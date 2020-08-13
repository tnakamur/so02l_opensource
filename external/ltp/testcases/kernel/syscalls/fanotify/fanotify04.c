// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2013 SUSE.  All Rights Reserved.
 *
 * Started by Jan Kara <jack@suse.cz>
 *
 * DESCRIPTION
 *     Check various fanotify special flags
 */

#define _GNU_SOURCE
#include "config.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/syscall.h>
#include "tst_test.h"
#include "fanotify.h"

#if defined(HAVE_SYS_FANOTIFY_H)
#include <sys/fanotify.h>

#define EVENT_MAX 1024
/* size of the event structure, not counting name */
#define EVENT_SIZE  (sizeof (struct fanotify_event_metadata))
/* reasonable guess as to size of 1024 events */
#define EVENT_BUF_LEN        (EVENT_MAX * EVENT_SIZE)

#define BUF_SIZE 256
#define TST_TOTAL 9

static char fname[BUF_SIZE];
static char sname[BUF_SIZE];
static char dir[BUF_SIZE];
static int fd_notify;

static int len;
static char event_buf[EVENT_BUF_LEN];

static char *expect_str_fail(int expect)
{
	if (expect == 0)
		return "failed";
	return "unexpectedly succeeded";
}

static char *expect_str_pass(int expect)
{
	if (expect == 0)
		return "succeeded";
	return "failed";
}

static void check_mark(char *file, unsigned long long flag, char *flagstr,
		       int expect, void (*test_event)(char *))
{
	if (fanotify_mark(fd_notify, FAN_MARK_ADD | flag, FAN_OPEN, AT_FDCWD,
			  file) != expect) {
		tst_res(TFAIL,
			"fanotify_mark (%d, FAN_MARK_ADD | %s, FAN_OPEN, "
			"AT_FDCWD, '%s') %s", fd_notify, flagstr, file,
			expect_str_fail(expect));
	} else {
		tst_res(TPASS,
			"fanotify_mark (%d, FAN_MARK_ADD | %s, FAN_OPEN, "
			"AT_FDCWD, '%s') %s", fd_notify, flagstr, file,
			expect_str_pass(expect));

		/* If we expected failure there's nothing to clean up */
		if (expect == -1)
			return;

		if (test_event)
			test_event(file);

		if (fanotify_mark(fd_notify, FAN_MARK_REMOVE | flag,
				  FAN_OPEN, AT_FDCWD, file) < 0) {
			tst_brk(TBROK | TERRNO,
				"fanotify_mark (%d, FAN_MARK_REMOVE | %s, "
				"FAN_OPEN, AT_FDCWD, '%s') failed",
				fd_notify, flagstr, file);
		}
	}
}

#define CHECK_MARK(file, flag, expect, func) check_mark(file, flag, #flag, expect, func)

static void do_open(char *file, int flag)
{
	int fd;

	fd = SAFE_OPEN(file, O_RDONLY | flag);
	SAFE_CLOSE(fd);
}

static void open_file(char *file)
{
	do_open(file, 0);
}

static void open_dir(char *file)
{
	do_open(file, O_DIRECTORY);
}

static void verify_event(int mask)
{
	int ret;
	struct fanotify_event_metadata *event;
	struct stat st;

	/* Read the event */
	ret = SAFE_READ(0, fd_notify, event_buf + len,
			EVENT_BUF_LEN - len);
	event = (struct fanotify_event_metadata *)&event_buf[len];
	len += ret;

	if (event->mask != FAN_OPEN) {
		tst_res(TFAIL, "got unexpected event %llx",
			(unsigned long long)event->mask);
	} else if (fstat(event->fd, &st) < 0) {
		tst_res(TFAIL, "failed to stat event->fd (%s)",
			strerror(errno));
	} else if ((int)(st.st_mode & S_IFMT) != mask) {
		tst_res(TFAIL, "event->fd points to object of different type "
			"(%o != %o)", st.st_mode & S_IFMT, mask);
	} else {
		tst_res(TPASS, "event generated properly for type %o", mask);
	}
	if (event->fd != FAN_NOFD)
		SAFE_CLOSE(event->fd);
}

static void do_open_test(char *file, int flag, int mask)
{
	do_open(file, flag);

	verify_event(mask);
}

static void test_open_file(char *file)
{
	do_open_test(file, 0, S_IFREG);
}

static void verify_no_event(void)
{
	int ret;

	ret = read(fd_notify, event_buf + len, EVENT_BUF_LEN - len);
	if (ret != -1) {
		struct fanotify_event_metadata *event;

		event = (struct fanotify_event_metadata *)&event_buf[len];
		tst_res(TFAIL, "seen unexpected event (mask %llx)",
			(unsigned long long)event->mask);
		/* Cleanup fd from the event */
		if (event->fd != FAN_NOFD)
			SAFE_CLOSE(event->fd);
	} else if (errno != EAGAIN) {
		tst_res(TFAIL | TERRNO, "read(%d, buf, %zu) failed", fd_notify,
			EVENT_BUF_LEN);
	} else {
		tst_res(TPASS, "No event as expected");
	}
}

static void test_open_symlink(char *file)
{
	/* Since mark is on a symlink, no event should be generated by opening a file */
	do_open(file, 0);
	verify_no_event();
}

void test01(void)
{
	/* Check ONLYDIR on a directory */
	CHECK_MARK(".", FAN_MARK_ONLYDIR, 0, NULL);

	/* Check ONLYDIR without a directory */
	CHECK_MARK(fname, FAN_MARK_ONLYDIR, -1, NULL);

	/* Check DONT_FOLLOW for a symlink */
	CHECK_MARK(sname, FAN_MARK_DONT_FOLLOW, 0, test_open_symlink);

	/* Check without DONT_FOLLOW for a symlink */
	CHECK_MARK(sname, 0, 0, test_open_file);

	/* Verify FAN_MARK_FLUSH destroys all inode marks */
	if (fanotify_mark(fd_notify, FAN_MARK_ADD,
			  FAN_OPEN, AT_FDCWD, fname) < 0) {
		tst_brk(TBROK | TERRNO,
			"fanotify_mark (%d, FAN_MARK_ADD, FAN_OPEN, "
			"AT_FDCWD, '%s') failed", fd_notify, fname);
	}
	if (fanotify_mark(fd_notify, FAN_MARK_ADD,
			  FAN_OPEN | FAN_ONDIR, AT_FDCWD, dir) < 0) {
		tst_brk(TBROK | TERRNO,
			"fanotify_mark (%d, FAN_MARK_ADD, FAN_OPEN | "
			"FAN_ONDIR, AT_FDCWD, '%s') failed", fd_notify,
			dir);
	}
	open_file(fname);
	verify_event(S_IFREG);
	open_dir(dir);
	verify_event(S_IFDIR);
	if (fanotify_mark(fd_notify, FAN_MARK_FLUSH,
			  0, AT_FDCWD, ".") < 0) {
		tst_brk(TBROK | TERRNO,
			"fanotify_mark (%d, FAN_MARK_FLUSH, 0, "
			"AT_FDCWD, '.') failed", fd_notify);
	}

	open_dir(dir);
	verify_no_event();
}

static void setup(void)
{
	int fd;

	sprintf(fname, "fname_%d", getpid());
	fd = SAFE_OPEN(fname, O_RDWR | O_CREAT, 0644);
	SAFE_CLOSE(fd);

	sprintf(sname, "symlink_%d", getpid());
	SAFE_SYMLINK(fname, sname);

	sprintf(dir, "dir_%d", getpid());
	SAFE_MKDIR(dir, 0755);

	fd_notify = SAFE_FANOTIFY_INIT(FAN_CLASS_NOTIF | FAN_NONBLOCK,
					O_RDONLY);
}

static void cleanup(void)
{
	if (fd_notify > 0)
		SAFE_CLOSE(fd_notify);
}

static struct tst_test test = {
	.test_all = test01,
	.setup = setup,
	.cleanup = cleanup,
	.needs_tmpdir = 1,
	.needs_root = 1
};

#else
	TST_TEST_TCONF("system doesn't have required fanotify support");
#endif
