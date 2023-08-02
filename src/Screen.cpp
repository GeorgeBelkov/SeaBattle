#include "Screen.hpp"


void Screen::loadFont(sf::String const& font_path)
{
    font.loadFromFile(font_path);
}


void Screen::createBackground(sf::String const& img_path)
{
    texture.loadFromFile(img_path);     // creating a background texture
    background.setTexture(&texture);
}