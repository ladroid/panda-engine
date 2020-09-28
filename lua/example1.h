//
// Created by Lado on 28/9/20.
//

#ifndef UNTITLED_EXAMPLE1_H
#define UNTITLED_EXAMPLE1_H

#include <iostream>
#include <string>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

//    #include "lua/lua.h"
//    #include "lua/lauxlib.h"
//    #include "lua/lualib.h"
}

/*
 * EXAMPLE 1
 */
void example1() {
    //initialize the state
    lua_State *state = luaL_newstate();

    //load libraries
    luaL_openlibs(state);

    //do file
    luaL_dofile(state, "example.lua");

    //get global
    lua_getglobal(state, "square");

    //square function
    lua_pushnumber(state, 2);

    //square function arguments
    lua_pcall(state, 1, 1, 0);

    //square result
    int result = lua_tonumber(state, -1);
    std::cout << "result = " << result << std::endl;

    //get global variable
    lua_getglobal(state, "x");
    int x = lua_tonumber(state, -1);
    std::cout << "x = " << x << std::endl;
}

#endif //UNTITLED_EXAMPLE1_H
