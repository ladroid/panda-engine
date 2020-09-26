//
// Created by Lado on 3/7/20.
//

#ifndef LOTOS_UILABEL_H
#define LOTOS_UILABEL_H

#include "../EntityComponent.h"
#include "../../AssetManager.h"
#include "../../Game.hpp"
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <string>

class UILabel : public Component {
private:
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColor;
    SDL_Texture *labelTexture;
public:
    UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& color) : labelText(text), labelFont(font), textColor(color) {
        position.x = xpos;
        position.y = ypos;
        setLabelText(labelText, labelFont);
    }
    void setLabelText(std::string text, std::string font) {
        SDL_Surface *surf = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColor);
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);
        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
    }
    void draw() override {
        SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
    }
    ~UILabel() {

    }
};

#endif //LOTOS_UILABEL_H
