cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -ggdb ${CMAKE_CXX_FLAGS}")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMAKE/")

set(SOL2_HEADER /Volumes/MyPassport/ProgrammingLanguageDesign/BindCLua/sol2/include)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glew REQUIRED)
#find_package(Sol2 REQUIRED)
#find_package(LUABIND REQUIRED)
#find_package(Lua REQUIRED)

add_library(glad /usr/local/include/glad/include/glad.h /usr/local/include/glad/src/glad.c engine/3D/Entity/Graphics3D.h engine/3D/Entity/EntityComponent3D.cpp engine/3D/Entity/EntityComponent3D.h lua/test/testing.cpp)

include_directories("engine/" ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

include_directories(lua_script /usr/local/include/ ${SOL2_HEADER} ${LUA_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

#file(GLOB LIBRARIES lua/lib/liblua52.dylib)

add_executable(untitled main.cpp engine/2D/Game.cpp engine/2D/Texture.h engine/2D/Texture.cpp engine/2D/GameObject.h engine/2D/GameObject.cpp engine/2D/Map.h engine/2D/Map.cpp engine/2D/Entity/EntityComponent.h engine/2D/Entity/Components.h engine/2D/Entity/SpriteComponent.h engine/2D/Entity/Transform.h engine/2D/Vector2D.h engine/2D/Vector2D.cpp engine/2D/Entity/InputHandler.h engine/2D/Entity/Collider.h engine/2D/Collision.h engine/2D/Collision.cpp engine/2D/Entity/TileComponent.h engine/2D/Entity/EntityComponent.cpp engine/2D/Entity/Animation.h engine/2D/AssetManager.h engine/2D/AssetManager.cpp engine/2D/Entity/Projectile.h engine/2D/Entity/Projectile.h engine/2D/Entity/UI/UILabel.h engine/2D/Entity/Timer.h engine/2D/Entity/Audio.h engine/2D/Entity/Graphics2D.h engine/2D/Entity/UI/UIButton.h engine/2D/Entity/EnemySpawner.cpp engine/2D/Entity/EnemySpawner.h engine/2D/Entity/FollowMouseComponent.cpp engine/2D/Entity/FollowMouseComponent.h engine/2D/Entity/MouseController.cpp engine/2D/Entity/MouseController.h)
add_executable(Test engine/3D/testingGL.cpp engine/3D/Entity/stb_image.h engine/3D/Entity/Texture.cpp engine/3D/Entity/Texture.h)

add_executable(lua_script lua/test_lua_script.cpp lua/test/example1.h lua/test/example2.h lua/test/testing.cpp lua/game/lua_game.h engine/2D/Game.cpp engine/2D/Texture.h engine/2D/Texture.cpp engine/2D/GameObject.h engine/2D/GameObject.cpp engine/2D/Map.h engine/2D/Map.cpp engine/2D/Entity/EntityComponent.h engine/2D/Entity/Components.h engine/2D/Entity/SpriteComponent.h engine/2D/Entity/Transform.h engine/2D/Vector2D.h engine/2D/Vector2D.cpp engine/2D/Entity/InputHandler.h engine/2D/Entity/Collider.h engine/2D/Collision.h engine/2D/Collision.cpp engine/2D/Entity/TileComponent.h engine/2D/Entity/EntityComponent.cpp engine/2D/Entity/Animation.h engine/2D/AssetManager.h engine/2D/AssetManager.cpp engine/2D/Entity/Projectile.h engine/2D/Entity/Projectile.h engine/2D/Entity/UI/UILabel.h engine/2D/Entity/Timer.h engine/2D/Entity/Audio.h engine/2D/Entity/Graphics2D.h engine/2D/Entity/UI/UIButton.h engine/2D/Entity/EnemySpawner.cpp engine/2D/Entity/EnemySpawner.h engine/2D/Entity/FollowMouseComponent.cpp engine/2D/Entity/FollowMouseComponent.h engine/2D/Entity/MouseController.cpp engine/2D/Entity/MouseController.h)

target_include_directories(glad PUBLIC /usr/local/include/)
#target_include_directories(lua_script PUBLIC ${LUA_INCLUDE_DIR})
target_link_libraries(untitled ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})

#target_link_libraries(lua_script ${LIBRARIES})
target_link_libraries(lua_script ${LUA_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})
message("   *** Lua include: ${LUA_INCLUDE_DIR}")
message("  *** Lua include lib: ${LUA_LIBRARY}")
message("  *** Lua include header: ${SOL2_HEADER}")
#message("  *** Lua include lib: ${LIBRARIES}")