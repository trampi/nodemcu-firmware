#include "module.h"
#include "lauxlib.h"
#include "platform.h"
#include "hydrogen.h"

static int lua_hydro_random_uniform(lua_State *L) {
  lua_pushnumber(L, hydro_random_uniform(lua_tonumber(L, 1)));
  return 1;
}

static int lua_hydro_random_u32(lua_State *L) {
  lua_pushnumber(L, hydro_random_u32());
  return 1;
}

static int lua_hydro_init(lua_State *L) {
  lua_pushnumber(L, hydro_init());
  return 1;
}

static const LUA_REG_TYPE libhydrogen_map[] = {
  { LSTRKEY( "random_u32" ),         LFUNCVAL( lua_hydro_random_u32 ) },
  { LSTRKEY( "random_uniform" ),            LFUNCVAL( lua_hydro_random_uniform ) },
  { LSTRKEY( "init" ),            LFUNCVAL( lua_hydro_init ) },

  { LNILKEY, LNILVAL }
};

NODEMCU_MODULE(LIBHYDROGEN, "libhydrogen", libhydrogen_map, NULL);
