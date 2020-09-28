//
// Created by Lado on 27/9/20.
//

#include <iostream>
#include "example2.h"

extern "C" {
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}

int main() {
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    RegisterPerson(l);
    luaL_dofile(l, "func.lua");
}