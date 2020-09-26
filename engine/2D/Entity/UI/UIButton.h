//
// Created by Lado on 12/7/20.
//

#ifndef LOTOS_UIBUTTON_H
#define LOTOS_UIBUTTON_H

#include <string>
#include "../EntityComponent.h"
#include "../../Game.hpp"
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"

class UIButton : public Component {
private:
    SDL_Rect position;
    SDL_Color btnColor;
    bool pressed = false;
    std::string buttonFont;
    SDL_Texture *textureButton;
    std::string textButton;
    const char *file;
public:
    UIButton() {  }

    UIButton(int xpos, int ypos, std::string text, std::string font, SDL_Color &color) : textButton(text), buttonFont(font), btnColor(color) {
        position.x = xpos;
        position.y = ypos;
        setLabelButton(textButton, buttonFont);
    }

    UIButton(int xpos, int ypos, std::string text, std::string font, SDL_Color &color, const char* filePath) : textButton(text), buttonFont(font), btnColor(color), file(filePath) {
        position.x = xpos;
        position.y = ypos;
        setLabelButton(textButton, buttonFont);
    }

    void setLabelButton(std::string text, std::string font) {
        SDL_Surface *surf = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), btnColor);
        textureButton = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);
        SDL_QueryTexture(textureButton, nullptr, nullptr, &position.w, &position.h);
    }

    void update() override {
        SDL_SetRenderDrawColor(Game::renderer, btnColor.r, btnColor.g, btnColor.b, btnColor.a);
        if(pressed) {
            pressed = false;
        } else {
            pressed = true;
        }
    }
    void draw() override {
        SDL_RenderDrawRect(Game::renderer, &position);
        //SDL_Surface *surf = IMG_Load(file);
        //SDL_FillRect(surf, &position, SDL_MapRGB(surf->format, btnColor.r, btnColor.g, btnColor.b));
        SDL_RenderCopy(Game::renderer, textureButton, nullptr, &position);
        //SDL_FreeSurface(surf);
    }
    ~UIButton() {

    }
};

#endif //LOTOS_UIBUTTON_H
