#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.hpp"


class AboutScreen : public Screen
{
public:
    AboutScreen(sf::Vector2f& desctop_size, sf::Texture texture, sf::Font font)
        : Screen(desctop_size, texture, font) {}
    ~AboutScreen() = default;

    void aboutGame(sf::RenderWindow& about_window);
    void aboutScreenDraw(sf::RenderWindow& about_window);
};
