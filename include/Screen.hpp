#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>


constexpr static unsigned int CHARACTER_SIZE = 100;         // font size


// Class Screen is the Parent of all Game Screens. It helps you to configurate sf::RenderWindow.
class Screen
{
protected:
    sf::RectangleShape background;
    sf::Texture background_texture;
    sf::Font font;

public:
    Screen(sf::Vector2f& desctop_size)
        : background(desctop_size), background_texture(sf::Texture()), font(sf::Font()) {}
    ~Screen() = default;
    Screen(Screen& screen) = delete;
    Screen& operator=(Screen& screen) = delete;
    
    sf::RectangleShape getBackground() const { return background; }
    
    void setFont(sf::Font& font);
    void setTexture(sf::Texture& texture);
    void setBackground();
};
