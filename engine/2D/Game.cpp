//
// Created by Lado on 2/6/20.
//

#include "Game.hpp"
#include "Map.h"
#include "Entity/Components.h"
#include "Vector2D.h"
#include <iostream>
#include "Entity/InputHandler.h"
#include "Collision.h"
#include "Entity/Collider.h"
#include "Entity/UI/UILabel.h"
#include "Entity/UI/UIButton.h"

SDL_Renderer *Game::renderer = nullptr;
Map *map;

SDL_Event Game::event;

Manage manage;
auto& player(manage.addEntity());

auto& tiles(manage.getGroup(Game::groupMap));
auto& players(manage.getGroup(Game::groupPlayers));
auto& colliders(manage.getGroup(Game::groupColliders));
auto& projectiles(manage.getGroup(Game::groupProjectiles));

auto& label(manage.addEntity());

auto &button(manage.addEntity());

bool Game::isRunning = false;

SDL_Rect Game::camera = {0, 0, 800, 640};

AssetManager* Game::assets = new AssetManager(&manage);

Game::Game() {}

/*
 * GAME INITIALIZATION
 * SET TITLE POSITIONS AND FALG FOR FULL SCREEN
 */
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsytsem Initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window) {
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;
    } else {
        isRunning = false;
    }
    if(TTF_Init() == -1) {
        std::cout << "Error SDL_TTF" << std::endl;
    }

    assets->addTexture("terrain", "/Volumes/MyPassport/ProgrammingLanguageDesign/ProgrammingLanguage/Lotos/src/classes/engine/assert/terrain_ss.png");
    assets->addTexture("player", "/Volumes/MyPassport/ProgrammingLanguageDesign/ProgrammingLanguage/Lotos/src/classes/engine/assert/player_anims.png");
    assets->addTexture("projectile", "/Volumes/MyPassport/ProgrammingLanguageDesign/ProgrammingLanguage/Lotos/src/classes/engine/assert/proj.png");

    assets->addFont("arial", "/Volumes/MyPassport/ProgrammingLanguageDesign/ProgrammingLanguage/Lotos/src/classes/engine/assert/arial.ttf", 16);

    map = new Map("terrain", 3, 32);

    map->LoadMap("/Volumes/MyPassport/ProgrammingLanguageDesign/ProgrammingLanguage/Lotos/src/classes/engine/assert/mapNew.map", 25, 20);

    player.addComponents<Transform>(4);
    player.addComponents<SpriteComponent>("player", true);
    player.addComponents<InputHandler>();
    player.addComponents<Collider>("player");
    player.addGroup(groupPlayers);

    SDL_Color white = {255, 255,255, 255};
    label.addComponents<UILabel>(10, 10, "Hello, World!", "arial", white);

    SDL_Color col = {123, 234,145, 100};
    button.addComponents<UIButton>(50, 50, "Press", "arial", col);

    assets->createProjectile(Vector2D(600, 600), Vector2D(2,0),200, 2, "projectile");
    assets->createProjectile(Vector2D(600, 620), Vector2D(2, 0), 200, 2, "projectile");
    assets->createProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
    assets->createProjectile(Vector2D(600, 600), Vector2D(2, -1), 200, 2, "projectile");
}

/*
 * EVENTS PRESSING ESQ FOR QUIT
 */
void Game::handleEvents() {

    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                }
            case SDL_MOUSEBUTTONDOWN:
                button.init_event(&event.button);
                break;
            default:
                break;
        }
    }
}

/*
 * SET HEIGHT AND WIDTH FOR IMAGE
 */
void Game::update() {
    SDL_Rect playerCol = player.getComponent<Collider>().collider;
    Vector2D playerPos = player.getComponent<Transform>().position;

    std::cout << playerPos << std::endl;
//    auto light2D = new Light2D(Vector2D(400, 320), 3.0, 4.0);
//    light2D->draw();
//    std::stringstream ss;
//    ss << "Player pos: ";
//    label.getComponent<UILabel>().setLabelText(ss.str(), "arial");

    manage.refresh();
    manage.update();

    button.update();

    for(auto &c : colliders) {
        SDL_Rect cColRect = c->getComponent<Collider>().collider;
        if(Collision::AABB(cColRect, playerCol)) {
            player.getComponent<Transform>().position = playerPos;
        }
    }

    for(auto& p : projectiles) {
        if(Collision::AABB(player.getComponent<Collider>().collider, p->getComponent<Collider>().collider)) {
            std::cout << "Hit player!" << std::endl;
            p->destroy();
        }
    }

    camera.x = player.getComponent<Transform>().position.x - 400;
    camera.y = player.getComponent<Transform>().position.y - 320;

    if(camera.x < 0) {
        camera.x = 0;
    }
    if(camera.y < 0) {
        camera.y = 0;
    }
    if(camera.x > camera.w) {
        camera.x = camera.w;
    }
    if(camera.y > camera.h) {
        camera.y = camera.h;
    }
}

/*
 * MAKE RENDER
 */
void Game::render() {
    SDL_RenderClear(renderer);
    for(auto& t : tiles) {
        t->draw();
    }
    for(auto &c : colliders) {
        c->draw();
    }
    for(auto& p : players) {
        p->draw();
    }
    for(auto& p : projectiles) {
        p->draw();
    }
    label.draw();
    button.draw();

    //manage.draw();
    SDL_RenderPresent(renderer);
}

/*
 * CLEANING EVERYTHING
 */
void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

Game::~Game() { }