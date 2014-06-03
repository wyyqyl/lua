/*
** $Id: ldebug.h,v 2.7.1.1 2013/04/12 18:48:47 roberto Exp $
** Auxiliary functions from Debug Interface module
** See Copyright Notice in lua.h
*/

#ifndef ldebug_h
#define ldebug_h


#include "lstate.h"


#define pcRel(pc, p)	(cast(int, (pc) - (p)->code) - 1)

#define getfuncline(f,pc)	(((f)->lineinfo) ? (f)->lineinfo[pc] : 0)

#define resethookcount(L)	(L->hookcount = L->basehookcount)

/* Active Lua function (given call info) */
#define ci_func(ci)		(clLvalue((ci)->func))


LUAI_FUNC l_noret luaG_typeerror (lua_State *L, const TValue *o,
                                                const char *opname);
LUAI_FUNC l_noret luaG_concaterror (lua_State *L, StkId p1, StkId p2);
LUAI_FUNC l_noret luaG_aritherror (lua_State *L, const TValue *p1,
                                                 const TValue *p2);
LUAI_FUNC l_noret luaG_ordererror (lua_State *L, const TValue *p1,
                                                 const TValue *p2);
LUAI_FUNC l_noret luaG_runerror (lua_State *L, const char *fmt, ...);
LUAI_FUNC l_noret luaG_errormsg (lua_State *L);


#if defined(LUA_DEBUG)

#include <stdio.h>

#define lua_dumpkey(tt) { \
  switch (ttypenv(tt)) { \
  case LUA_TNIL: printf("NIL"); break; \
  case LUA_TBOOLEAN: printf("%d", bvalue(tt)); break; \
  case LUA_TNUMBER: printf("%lf", nvalue(tt)); break; \
  case LUA_TSTRING: printf("%s", svalue(tt)); break; \
  case LUA_TTABLE: printf("Tbl 0x%p", hvalue(tt)); break; \
  case LUA_TFUNCTION: printf("Func 0x%p", val_(tt).f); break; \
  case LUA_TUSERDATA: printf("UD 0x%0p", rawuvalue(tt)); break; \
  default: __asm { int 3 } printf("%d", ttypenv(tt)); break; \
  } \
}

LUAI_FUNC void luaG_dumptable(lua_State* L, Table* t);
LUAI_FUNC void luaG_dumpnodeindex(Table* t, Node* node, const char* msg);
LUAI_FUNC void luaG_dumpnode(Node* node);
#endif

#endif
