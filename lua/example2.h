//
// Created by Lado on 28/9/20.
//

#ifndef UNTITLED_EXAMPLE2_H
#define UNTITLED_EXAMPLE2_H

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
 * EXAMPLE 2
 */
class Person {
private:
    std::string name;
    int age;
public:
    Person(std::string name, int age) : name(name), age(age) {}
    void set_name(std::string name) {
        this->name = name;
    }
    void set_age(int age) {
        this->age = age;
    }
    std::string get_name() {
        return name;
    }
    int get_age() {
        return age;
    }
};

int l_Person_constructor(lua_State *L) {
    const char *name = luaL_checkstring(L, 1);
    int age = luaL_checkinteger(L, 2);
    Person **udata = (Person **) lua_newuserdata(L, sizeof(Person));
    *udata = new Person(name, age);

    luaL_getmetatable(L, "luaL_Person");
    lua_setmetatable(L, -2);

    return 1;
}

Person *l_CheckPerson(lua_State *L, int n) {
    return *(Person **) luaL_checkudata(L, n, "luaL_Person");
}

int l_Person_setName(lua_State *L) {
    Person *p = l_CheckPerson(L, 1);
    std::string name = luaL_checkstring(L, 2);
    name = p->get_name();
    lua_pushstring(L, name.c_str());
    return 1;
}

int l_Person_setAge(lua_State *L) {
    Person *p = l_CheckPerson(L, 1);
    int age = luaL_checkinteger(L, 2);
    age = p->get_age();
    lua_pushinteger(L, age);
    return 1;
}

int l_Person_getName(lua_State *L) {
    Person *p = l_CheckPerson(L, 1);
    std::string name = p->get_name();
    //Person *p = reinterpret_cast<Person *>(lua_touserdata(L, 1));
    lua_pushstring(L, name.c_str());
    return 1;
}

int l_Person_getAge(lua_State *L) {
    Person *p = l_CheckPerson(L, 1);
    int age = p->get_age();
    lua_pushinteger(L, age);
    return 1;
}

int l_Person_destructor(lua_State *L) {
    Person *p = l_CheckPerson(L, 1);
    delete p;
    return 0;
}

void RegisterPerson(lua_State *L) {
    luaL_Reg sPersonRegs[] = {
            {"new", l_Person_constructor},
            {"set_name", l_Person_setName},
            {"get_name", l_Person_getName},
            {"set_age", l_Person_setAge},
            {"get_age", l_Person_getAge},
            {"__gc", l_Person_destructor},
            {NULL, NULL}
    };
    luaL_newmetatable(L, "luaL_Person");
    //luaL_setfuncs(L, sPersonRegs, 0); //same as function below

    luaL_register(L, NULL, sPersonRegs);

    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_setglobal(L, "Person");
}

#endif //UNTITLED_EXAMPLE2_H
