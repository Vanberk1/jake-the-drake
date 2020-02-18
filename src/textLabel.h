#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class TextLabel {
private:
    SDL_Renderer* m_Renderer;
    std::string m_Text;
    TTF_Font* m_Font;
    SDL_Texture* m_Texture;
    SDL_Rect m_Position;
    SDL_Color m_Color;
public:
    TextLabel();
    void createLabel(std::string text, SDL_Color color);
    void draw(SDL_Renderer* renderer);
    SDL_Texture* getTexture() const;
    SDL_Rect* getPosition();

    void init(SDL_Renderer* renderer, TTF_Font* font);
    void setText(std::string text);
    void setPosition(SDL_Rect position);
};