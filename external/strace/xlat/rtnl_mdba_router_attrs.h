/* Generated by ./xlat/gen.sh from ./xlat/rtnl_mdba_router_attrs.in; do not edit. */
#if !(defined(MDBA_ROUTER_UNSPEC) || (defined(HAVE_DECL_MDBA_ROUTER_UNSPEC) && HAVE_DECL_MDBA_ROUTER_UNSPEC))
# define MDBA_ROUTER_UNSPEC 0
#endif
#if !(defined(MDBA_ROUTER_PORT) || (defined(HAVE_DECL_MDBA_ROUTER_PORT) && HAVE_DECL_MDBA_ROUTER_PORT))
# define MDBA_ROUTER_PORT 1
#endif

#ifdef IN_MPERS

# error static const struct xlat rtnl_mdba_router_attrs in mpers mode

#else

static
const struct xlat rtnl_mdba_router_attrs[] = {
 XLAT(MDBA_ROUTER_UNSPEC),
 XLAT(MDBA_ROUTER_PORT),
 XLAT_END
};

#endif /* !IN_MPERS */