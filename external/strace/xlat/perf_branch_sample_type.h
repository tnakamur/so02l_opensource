/* Generated by ./xlat/gen.sh from ./xlat/perf_branch_sample_type.in; do not edit. */
#if !(defined(PERF_SAMPLE_BRANCH_USER) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_USER) && HAVE_DECL_PERF_SAMPLE_BRANCH_USER))
# define PERF_SAMPLE_BRANCH_USER 1 << 0
#endif
#if !(defined(PERF_SAMPLE_BRANCH_KERNEL) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_KERNEL) && HAVE_DECL_PERF_SAMPLE_BRANCH_KERNEL))
# define PERF_SAMPLE_BRANCH_KERNEL 1 << 1
#endif
#if !(defined(PERF_SAMPLE_BRANCH_HV) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_HV) && HAVE_DECL_PERF_SAMPLE_BRANCH_HV))
# define PERF_SAMPLE_BRANCH_HV 1 << 2
#endif
#if !(defined(PERF_SAMPLE_BRANCH_ANY) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_ANY) && HAVE_DECL_PERF_SAMPLE_BRANCH_ANY))
# define PERF_SAMPLE_BRANCH_ANY 1 << 3
#endif
#if !(defined(PERF_SAMPLE_BRANCH_ANY_CALL) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_ANY_CALL) && HAVE_DECL_PERF_SAMPLE_BRANCH_ANY_CALL))
# define PERF_SAMPLE_BRANCH_ANY_CALL 1 << 4
#endif
#if !(defined(PERF_SAMPLE_BRANCH_ANY_RETURN) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_ANY_RETURN) && HAVE_DECL_PERF_SAMPLE_BRANCH_ANY_RETURN))
# define PERF_SAMPLE_BRANCH_ANY_RETURN 1 << 5
#endif
#if !(defined(PERF_SAMPLE_BRANCH_IND_CALL) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_IND_CALL) && HAVE_DECL_PERF_SAMPLE_BRANCH_IND_CALL))
# define PERF_SAMPLE_BRANCH_IND_CALL 1 << 6
#endif
#if !(defined(PERF_SAMPLE_BRANCH_ABORT_TX) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_ABORT_TX) && HAVE_DECL_PERF_SAMPLE_BRANCH_ABORT_TX))
# define PERF_SAMPLE_BRANCH_ABORT_TX 1 << 7
#endif
#if !(defined(PERF_SAMPLE_BRANCH_IN_TX) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_IN_TX) && HAVE_DECL_PERF_SAMPLE_BRANCH_IN_TX))
# define PERF_SAMPLE_BRANCH_IN_TX 1 << 8
#endif
#if !(defined(PERF_SAMPLE_BRANCH_NO_TX) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_NO_TX) && HAVE_DECL_PERF_SAMPLE_BRANCH_NO_TX))
# define PERF_SAMPLE_BRANCH_NO_TX 1 << 9
#endif
#if !(defined(PERF_SAMPLE_BRANCH_COND) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_COND) && HAVE_DECL_PERF_SAMPLE_BRANCH_COND))
# define PERF_SAMPLE_BRANCH_COND 1 << 10
#endif
#if !(defined(PERF_SAMPLE_BRANCH_CALL_STACK) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_CALL_STACK) && HAVE_DECL_PERF_SAMPLE_BRANCH_CALL_STACK))
# define PERF_SAMPLE_BRANCH_CALL_STACK 1 << 11
#endif
#if !(defined(PERF_SAMPLE_BRANCH_IND_JUMP) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_IND_JUMP) && HAVE_DECL_PERF_SAMPLE_BRANCH_IND_JUMP))
# define PERF_SAMPLE_BRANCH_IND_JUMP 1 << 12
#endif
#if !(defined(PERF_SAMPLE_BRANCH_CALL) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_CALL) && HAVE_DECL_PERF_SAMPLE_BRANCH_CALL))
# define PERF_SAMPLE_BRANCH_CALL 1 << 13
#endif
#if !(defined(PERF_SAMPLE_BRANCH_NO_FLAGS) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_NO_FLAGS) && HAVE_DECL_PERF_SAMPLE_BRANCH_NO_FLAGS))
# define PERF_SAMPLE_BRANCH_NO_FLAGS 1 << 14
#endif
#if !(defined(PERF_SAMPLE_BRANCH_NO_CYCLES) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_NO_CYCLES) && HAVE_DECL_PERF_SAMPLE_BRANCH_NO_CYCLES))
# define PERF_SAMPLE_BRANCH_NO_CYCLES 1 << 15
#endif
#if !(defined(PERF_SAMPLE_BRANCH_TYPE_SAVE) || (defined(HAVE_DECL_PERF_SAMPLE_BRANCH_TYPE_SAVE) && HAVE_DECL_PERF_SAMPLE_BRANCH_TYPE_SAVE))
# define PERF_SAMPLE_BRANCH_TYPE_SAVE 1 << 16
#endif

#ifdef IN_MPERS

# error static const struct xlat perf_branch_sample_type in mpers mode

#else

static
const struct xlat perf_branch_sample_type[] = {
 XLAT(PERF_SAMPLE_BRANCH_USER),
 XLAT(PERF_SAMPLE_BRANCH_KERNEL),
 XLAT(PERF_SAMPLE_BRANCH_HV),
 XLAT(PERF_SAMPLE_BRANCH_ANY),
 XLAT(PERF_SAMPLE_BRANCH_ANY_CALL),
 XLAT(PERF_SAMPLE_BRANCH_ANY_RETURN),
 XLAT(PERF_SAMPLE_BRANCH_IND_CALL),
 XLAT(PERF_SAMPLE_BRANCH_ABORT_TX),
 XLAT(PERF_SAMPLE_BRANCH_IN_TX),
 XLAT(PERF_SAMPLE_BRANCH_NO_TX),
 XLAT(PERF_SAMPLE_BRANCH_COND),
 XLAT(PERF_SAMPLE_BRANCH_CALL_STACK),
 XLAT(PERF_SAMPLE_BRANCH_IND_JUMP),
 XLAT(PERF_SAMPLE_BRANCH_CALL),
 XLAT(PERF_SAMPLE_BRANCH_NO_FLAGS),
 XLAT(PERF_SAMPLE_BRANCH_NO_CYCLES),
 XLAT(PERF_SAMPLE_BRANCH_TYPE_SAVE),
 XLAT_END
};

#endif /* !IN_MPERS */
