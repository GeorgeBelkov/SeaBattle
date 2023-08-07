#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.hpp"


// Represents About Screen (Game menu -> About game)
class AboutScreen : public Screen
{
private:
    sf::Text title;
    sf::Text topic;

public:
    AboutScreen(sf::Vector2f& desctop_size, sf::String title, sf::String topic)
        : Screen(desctop_size), title(sf::Text(title, font, CHARACTER_SIZE)), topic(sf::Text(topic, font, CHARACTER_SIZE / 3)) {}
    ~AboutScreen() = default;
    AboutScreen(AboutScreen& other) = delete;
    AboutScreen& operator=(AboutScreen& other) = delete;

    void runAboutScreen(sf::RenderWindow& about_window);
    void setTitle(sf::Color color);
    void setTopic(sf::Color color);
};