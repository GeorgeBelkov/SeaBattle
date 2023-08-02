#pragma once

#include <SFML/Graphics.hpp>


class Screen
{
public:
    Screen(sf::Vector2f& desctop_size, sf::Texture texture, sf::Font font)
        : background(desctop_size), texture(texture), font(font) {}
    ~Screen() {}

    
    sf::RectangleShape getBackground() const { return background; }
    void loadFont(sf::String const& font_path);
    void createBackground(sf::String const& img_path);

protected:
    sf::RectangleShape background;
    sf::Texture texture;
    sf::Font font;

private:
    Screen(Screen& screen);
    Screen& operator=(Screen& screen);
};
