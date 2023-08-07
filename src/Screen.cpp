#include "Screen.hpp"


void Screen::setFont(sf::Font& font)
{
    this->font = font;
}


void Screen::setTexture(sf::Texture& texture)
{
    this->background_texture = texture;
}


void Screen::setBackground()
{
    background.setTexture(&background_texture);
}