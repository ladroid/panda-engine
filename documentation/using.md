# How to use

The whole example can be found in [Game.cpp](https://github.com/ladroid/lotos-lang/blob/master/engine/2D/Game.cpp).


For adding entity component call the **Manage** class

Example:
```c++
Manage manager;
auto player(manager.addEntity());
```

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









