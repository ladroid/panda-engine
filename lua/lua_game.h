//
// Created by Lado on 28/9/20.
//

#ifndef UNTITLED_LUA_GAME_H
#define UNTITLED_LUA_GAME_H

#include <iostream>
#include "SDL2/SDL.h"
#include "../engine/2D/Game.hpp"
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

//    #include "lua/lua.h"
//    #include "lua/lauxlib.h"
//    #include "lua/lualib.h"
}

int l_Game_constructor(lua_State *l) {
    Game **udata = (Game **) lua_newuserdata(l, sizeof(Game));
    *udata = new Game();

    luaL_getmetatable(l, "luaL_Game");
    lua_setmetatable(l, -2);
    return 1;
}

Game *l_CheckGame(lua_State *L, int n) {
    return *(Game **) luaL_checkudata(L, n, "luaL_Game");
}

int l_Game_init(lua_State *L) {
    Game *p = l_CheckGame(L, 1);
    std::string title = luaL_checkstring(L, 2);
    std::string sdl_window_centered = luaL_checkstring(L, 3);
    std::string sdl_window_centered2 = luaL_checkstring(L, 4);
    int width = luaL_checkinteger(L, 5);
    int height = luaL_checkinteger(L, 6);
    bool flag = lua_toboolean(L, 7);

    p->init(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flag);
    lua_pushstring(L, title.c_str());
    lua_pushstring(L, sdl_window_centered.c_str());
    lua_pushstring(L, sdl_window_centered2.c_str());
    lua_pushinteger(L, width);
    lua_pushinteger(L, height);
    lua_pushboolean(L, flag);
    return 1;
}

int l_Game_running(lua_State *L) {
    Game *p = l_CheckGame(L, 1);
    bool running = p->running();
    lua_pushboolean(L, running);
    return 1;
}

int l_Game_handleEvent(lua_State *L) {
    Game *p = l_CheckGame(L, 1);
    p->handleEvents();
    return 1;
}

int l_Game_update(lua_State *L) {
    Game *p = l_CheckGame(L, 1);
    p->update();
    return 1;
}

int l_Game_render(lua_State *L) {
    Game *p = l_CheckGame(L, 1);
    p->render();
    return 1;
}

int l_Game_clean(lua_State *L) {
    Game *p = l_CheckGame(L, 1);
    p->clean();
    return 1;
}

int l_Game_GetTicks(lua_State *L) {
    Uint32 ticks = SDL_GetTicks();
    lua_pushinteger(L, ticks);
    return 1;
}

int l_Game_Delay(lua_State *L) {
    Uint32 delay = luaL_checkinteger(L, 1);
    std::cout << "Delay " << delay << std::endl;
    SDL_Delay(delay);
    lua_pushinteger(L, delay);
    return 1;
}

int l_Game_destructor(lua_State *L) {
    Game *p = l_CheckGame(L, 1);
    delete p;
    return 0;
}

void RegisterGame(lua_State *L) {
    luaL_Reg sPersonRegs[] = {
            {"new", l_Game_constructor},
            {"init", l_Game_init},
            {"running", l_Game_running},
            {"handleEvent", l_Game_handleEvent},
            {"update", l_Game_update},
            {"render", l_Game_render},
            {"get_ticks", l_Game_GetTicks},
            {"delay", l_Game_Delay},
            {"clean", l_Game_clean},
            {"__gc", l_Game_destructor},
            {NULL, NULL}
    };
    luaL_newmetatable(L, "luaL_Game");
    luaL_setfuncs(L, sPersonRegs, 0); //same as function below

    //luaL_register(L, NULL, sPersonRegs);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, "Game");
}

#endif //UNTITLED_LUA_GAME_H
