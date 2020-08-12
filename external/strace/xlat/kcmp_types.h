/* Generated by ./xlat/gen.sh from ./xlat/kcmp_types.in; do not edit. */
#if !(defined(KCMP_FILE) || (defined(HAVE_DECL_KCMP_FILE) && HAVE_DECL_KCMP_FILE))
# define KCMP_FILE 0
#endif
#if !(defined(KCMP_VM) || (defined(HAVE_DECL_KCMP_VM) && HAVE_DECL_KCMP_VM))
# define KCMP_VM 1
#endif
#if !(defined(KCMP_FILES) || (defined(HAVE_DECL_KCMP_FILES) && HAVE_DECL_KCMP_FILES))
# define KCMP_FILES 2
#endif
#if !(defined(KCMP_FS) || (defined(HAVE_DECL_KCMP_FS) && HAVE_DECL_KCMP_FS))
# define KCMP_FS 3
#endif
#if !(defined(KCMP_SIGHAND) || (defined(HAVE_DECL_KCMP_SIGHAND) && HAVE_DECL_KCMP_SIGHAND))
# define KCMP_SIGHAND 4
#endif
#if !(defined(KCMP_IO) || (defined(HAVE_DECL_KCMP_IO) && HAVE_DECL_KCMP_IO))
# define KCMP_IO 5
#endif
#if !(defined(KCMP_SYSVSEM) || (defined(HAVE_DECL_KCMP_SYSVSEM) && HAVE_DECL_KCMP_SYSVSEM))
# define KCMP_SYSVSEM 6
#endif
#if !(defined(KCMP_EPOLL_TFD) || (defined(HAVE_DECL_KCMP_EPOLL_TFD) && HAVE_DECL_KCMP_EPOLL_TFD))
# define KCMP_EPOLL_TFD 7
#endif

#ifdef IN_MPERS

# error static const struct xlat kcmp_types in mpers mode

#else

static
const struct xlat kcmp_types[] = {
 XLAT(KCMP_FILE),
 XLAT(KCMP_VM),
 XLAT(KCMP_FILES),
 XLAT(KCMP_FS),
 XLAT(KCMP_SIGHAND),
 XLAT(KCMP_IO),
 XLAT(KCMP_SYSVSEM),
 XLAT(KCMP_EPOLL_TFD),
 XLAT_END
};

#endif /* !IN_MPERS */
