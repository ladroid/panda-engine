//
// Created by Lado on 27/9/20.
//

#include <iostream>
#include <string>
//#include "example2.h"
#include "lua_game.h"

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"

//    #include "lua/lua.h"
//    #include "lua/lauxlib.h"
//    #include "lua/lualib.h"
}

int main() {
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    //RegisterPerson(l);
    RegisterGame(l);
    luaL_dofile(l, "/Volumes/MyPassport/ProgrammingLanguageDesign/PandaEngine/lua/game.lua");
}