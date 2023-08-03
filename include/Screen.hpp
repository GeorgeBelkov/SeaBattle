#pragma once

#include <SFML/Graphics.hpp>

// Base class for window design
class Screen
{
public:
    Screen(sf::Vector2f& desctop_size, sf::Texture texture, sf::Font font)
        : background(desctop_size), texture(texture), font(font) {}
    ~Screen() = default;
    Screen(Screen& screen) = delete;
    Screen& operator=(Screen& screen) = delete;
    
    sf::RectangleShape getBackground() const { return background; }
    void loadFont(sf::String const& font_path);
    void createBackground(sf::String const& img_path);

protected:
    sf::RectangleShape background;
    sf::Texture texture;
    sf::Font font;
};
