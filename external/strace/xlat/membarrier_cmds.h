/* Generated by ./xlat/gen.sh from ./xlat/membarrier_cmds.in; do not edit. */
#if !(defined(MEMBARRIER_CMD_QUERY) || (defined(HAVE_DECL_MEMBARRIER_CMD_QUERY) && HAVE_DECL_MEMBARRIER_CMD_QUERY))
# define MEMBARRIER_CMD_QUERY 0
#endif
#if !(defined(MEMBARRIER_CMD_GLOBAL) || (defined(HAVE_DECL_MEMBARRIER_CMD_GLOBAL) && HAVE_DECL_MEMBARRIER_CMD_GLOBAL))
# define MEMBARRIER_CMD_GLOBAL 1 << 0
#endif
#if !(defined(MEMBARRIER_CMD_GLOBAL_EXPEDITED) || (defined(HAVE_DECL_MEMBARRIER_CMD_GLOBAL_EXPEDITED) && HAVE_DECL_MEMBARRIER_CMD_GLOBAL_EXPEDITED))
# define MEMBARRIER_CMD_GLOBAL_EXPEDITED 1 << 1
#endif
#if !(defined(MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED) || (defined(HAVE_DECL_MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED) && HAVE_DECL_MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED))
# define MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED 1 << 2
#endif
#if !(defined(MEMBARRIER_CMD_PRIVATE_EXPEDITED) || (defined(HAVE_DECL_MEMBARRIER_CMD_PRIVATE_EXPEDITED) && HAVE_DECL_MEMBARRIER_CMD_PRIVATE_EXPEDITED))
# define MEMBARRIER_CMD_PRIVATE_EXPEDITED 1 << 3
#endif
#if !(defined(MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED) || (defined(HAVE_DECL_MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED) && HAVE_DECL_MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED))
# define MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED 1 << 4
#endif
#if !(defined(MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE) || (defined(HAVE_DECL_MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE) && HAVE_DECL_MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE))
# define MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE 1 << 5
#endif
#if !(defined(MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE) || (defined(HAVE_DECL_MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE) && HAVE_DECL_MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE))
# define MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE 1 << 6
#endif

#ifdef IN_MPERS

# error static const struct xlat membarrier_cmds in mpers mode

#else

static
const struct xlat membarrier_cmds[] = {
 XLAT(MEMBARRIER_CMD_QUERY),
 XLAT(MEMBARRIER_CMD_GLOBAL),
 XLAT(MEMBARRIER_CMD_GLOBAL_EXPEDITED),
 XLAT(MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED),
 XLAT(MEMBARRIER_CMD_PRIVATE_EXPEDITED),
 XLAT(MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED),
 XLAT(MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE),
 XLAT(MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE),
 XLAT_END
};

#endif /* !IN_MPERS */
