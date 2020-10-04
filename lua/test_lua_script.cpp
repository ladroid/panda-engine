//
// Created by Lado on 27/9/20.
//

#include <iostream>
#include <string>
//#include "test/example2.h"
#include "game/lua_game.h"

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
//    //RegisterPerson(l);
//    //luaL_dofile(l, "/Volumes/MyPassport/ProgrammingLanguageDesign/PandaEngine/lua/test/func.lua");
    RegisterGame(l);
    luaL_dofile(l, "/Volumes/MyPassport/ProgrammingLanguageDesign/PandaEngine/lua/game/game.lua");

}