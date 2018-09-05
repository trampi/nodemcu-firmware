#include "c_stdio.h"
#include "c_stdlib.h"
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

// local result = libhydrogen.secretbox_encrypt(message, context, key)
static int lua_hydro_secretbox_encrypt(lua_State *L) {
  if (!lua_isstring(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L, 3)) {
    c_printf("invalid arguments");
    return 0;
  }

  const char *message = lua_tostring(L, 1);
  const size_t message_len = lua_strlen(L, 1);

  const char *context = lua_tostring(L, 2);
  const size_t context_len = lua_strlen(L, 2);

  const char *key = lua_tostring(L, 3);
  const size_t key_len = lua_strlen(L, 3);

  if (message_len == 0) {
    c_printf("invalid message length");
    return 0;
  } else if(context_len != hydro_secretbox_CONTEXTBYTES) {
    c_printf("invalid context length");
    return 0;
  } else if(key_len != hydro_secretbox_KEYBYTES) {
    c_printf("invalid key length");
    return 0;
  }

  size_t ciphertext_len = hydro_secretbox_HEADERBYTES + message_len;
  char ciphertext[ciphertext_len];
  hydro_secretbox_encrypt((uint8_t*)ciphertext, message, message_len, 0, context, (uint8_t*)key);
  lua_pushlstring(L, ciphertext, ciphertext_len);
  return 1;
}

static int lua_hydro_secretbox_decrypt(lua_State *L) {
  if (!lua_isstring(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L, 3)) {
    c_printf("invalid arguments");
    return 0;
  }

  const char *ciphertext = lua_tostring(L, 1);
  const size_t ciphertext_len = lua_strlen(L, 1);

  const char *context = lua_tostring(L, 2);
  const size_t context_len = lua_strlen(L, 2);

  const char *key = lua_tostring(L, 3);
  const size_t key_len = lua_strlen(L, 3);

  if (ciphertext_len < hydro_secretbox_HEADERBYTES + 1) {
    c_printf("invalid ciphertext length");
    return 0;
  } else if(context_len != hydro_secretbox_CONTEXTBYTES) {
    c_printf("invalid context length");
    return 0;
  } else if(key_len != hydro_secretbox_KEYBYTES) {
    c_printf("invalid key length");
    return 0;
  }

  size_t message_len = ciphertext_len - hydro_secretbox_HEADERBYTES;
  char message[message_len];
  if (hydro_secretbox_decrypt((uint8_t*)message, ciphertext, ciphertext_len, 0, context, (uint8_t*)key) != 0) {
    c_printf("decryption failed");
    return 0;
  }

  lua_pushlstring(L, message, message_len);
  return 1;
}

static const LUA_REG_TYPE libhydrogen_map[] = {
  { LSTRKEY( "random_u32" ),         LFUNCVAL( lua_hydro_random_u32 ) },
  { LSTRKEY( "random_uniform" ),            LFUNCVAL( lua_hydro_random_uniform ) },
  { LSTRKEY( "init" ),            LFUNCVAL( lua_hydro_init ) },
  { LSTRKEY( "secretbox_encrypt" ),            LFUNCVAL( lua_hydro_secretbox_encrypt ) },
  { LSTRKEY( "secretbox_decrypt" ),            LFUNCVAL( lua_hydro_secretbox_decrypt ) },

  { LNILKEY, LNILVAL }
};

NODEMCU_MODULE(LIBHYDROGEN, "libhydrogen", libhydrogen_map, NULL);
