#include "textLabel.h"

TextLabel::TextLabel() {

}

void TextLabel::init(SDL_Renderer* renderer, TTF_Font* font) {
    m_Renderer = renderer;
    m_Font = font;
    m_Position = { 0, 0, 0, 0 };
}

void TextLabel::createLabel(std::string text, SDL_Color color) {
    m_Text = text;
    m_Color = color;
    setText(text);
}

void TextLabel::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_Texture, NULL, &m_Position);
}

SDL_Texture* TextLabel::getTexture() const {
    return m_Texture;
}

SDL_Rect* TextLabel::getPosition() {
    return &m_Position;
}

void TextLabel::setText(std::string text) {
    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, text.c_str(), m_Color);
    m_Texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(m_Texture, NULL, NULL, &m_Position.w, &m_Position.h);
}

void TextLabel::setPosition(SDL_Rect position) {
    m_Position.x = position.x;
    m_Position.y = position.y;
    m_Position.w = position.w;
    m_Position.y = position.y;
}