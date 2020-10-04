//
// Created by Lado on 27/9/20.
//

#include <iostream>
#include <string>
#include "test/example2.h"
//#include "game/lua_game.h"

#include <sol/sol.hpp>

int main() {

//    lua_State *l = luaL_newstate();
//    luaL_openlibs(l);
//    RegisterPerson(l);
//    luaL_dofile(l, "/Volumes/MyPassport/ProgrammingLanguageDesign/PandaEngine/lua/test/func.lua");
//    RegisterGame(l);
//    luaL_dofile(l, "/Volumes/MyPassport/ProgrammingLanguageDesign/PandaEngine/lua/game/game.lua");

    sol::state lua;
    lua.open_libraries(sol::lib::base);

    lua["p1"] = Person();
    sol::usertype<Person> person_type = lua.new_usertype<Person>("person", sol::constructors<Person(), Person(std::string, int)>());
    person_type["name"] = sol::property(&Person::get_name, &Person::set_name);
    person_type["age"] = sol::property(&Person::get_age, &Person::set_age);
    lua.script_file("/Volumes/MyPassport/ProgrammingLanguageDesign/PandaEngine/lua/test/sol_test.lua");
}