# How to use

### How to write 2D games using Panda Engine

The whole example can be found in [Game.cpp](https://github.com/ladroid/lotos-lang/blob/master/engine/2D/Game.cpp).

----

#### Here you can find how to call and use some components.


For adding entity component call the **Manage** class

Example:
```c++
Manage manager;
auto player(manager.addEntity());
```
---
For adding labels for group make the enum

Example:
```c++
enum groupLabels : std::size_t {groupMap, groupPlayers, groupEnemies, groupColliders, groupProjectiles};
```

After put the labels into separate object

Example:
```c++
auto& tiles(manage.getGroup(Game::groupMap));
```
---
For using assets call the AssetManager

Example:
```c++
AssetManager* Game::assets = new AssetManager(&manage);
```
After we can add texture like in the example
```c++
assets->addTexture("NAME OF OBJECT", "PATH");
```
For adding fonts use 
```c++ 
assets->addFonts("NAME FONT", "PATH");
```
---
For adding map use
```c++ 
map = new Map(string id, int ms, int ts);
...
map->LoadMap("PATH", sizeX, sizeY);
```
---
Now the most important is adding components for objects like for main character or enemies
```c++ 
player.addComponents<Transform>(4);
player.addComponents<SpriteComponent>(ID, ANIMATION); string ID and bool ANIMATION
player.addComponents<InputHandler>();
player.addComponents<Collider>(ID); //string ID
player.addGroup(groupPlayers); //adding a grop label
```
---
For adding UIButton use
```c++ 
button.addComponents<UIButton>(SIZE_X, SIZE_Y, NAME, FONT, COLOUR);
/*
 * IMPORTANT COLOUR accept only SDL_Color
/*
```
---
For checking collision use
```c++ 
for(auto &c : colliders) {
    SDL_Rect cColRect = c->getComponent<Collider>().collider;
    if(Collision::AABB(cColRect, playerCol)) {
        player.getComponent<Transform>().position = playerPos;
    }
}
```
---
To display the object such as character use
```c++ 
for(auto& p : players) {
    p->draw();
}
```







