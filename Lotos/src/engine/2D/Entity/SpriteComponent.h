//
// Created by Lado on 11/6/20.
//

#ifndef LOTOS_SPRITECOMPONENT_H
#define LOTOS_SPRITECOMPONENT_H

#include <map>
#include "Components.h"
#include "SDL.h"
#include "Texture.h"
#include "Animation.h"
#include <string>

class SpriteComponent : public Component {
private:
    Transform *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    bool animated = false;
    int frames = 0;
    int speed = 100;
public:
    int animIndex = 0;
    std::map<const char*, Animation> animations;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    SpriteComponent(std::string id) {
        texture = Game::assets->getTexture(id);
    }

    SpriteComponent(std::string id, bool isAnimated) {
        animated = isAnimated;

        Animation idle = Animation(0, 3, 100);
        Animation walk = Animation(1, 8, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);

        play("Idle");

        texture = Game::assets->getTexture(id);
    }

    void setTexture(const char* path) {
        texture = Texture::LoadTexture(path);
    }

    void init() override {
        transform = &entity->getComponent<Transform>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() override {
        if(animated) {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }
        srcRect.y = animIndex * transform->height;
        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override {
        Texture::Draw(texture, srcRect, destRect, flip);
    }

    void play(const char* animName) {
        frames = animations[animName].frame;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }

    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }
};

#endif //LOTOS_SPRITECOMPONENT_H
