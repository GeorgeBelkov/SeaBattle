#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.hpp"


struct TextFeatures
{
    TextFeatures(unsigned int size, sf::String text, sf::Color color = sf::Color::Black)
        : color(color), text(text), characterSize(size) {}

    sf::Color color;
    sf::String text;
    unsigned int characterSize;
};



class AboutScreen : public Screen
{
public:
    AboutScreen(sf::Vector2f& desctop_size, sf::Texture texture, sf::Font font, sf::Text titlee, sf::Text topicc)
        : Screen(desctop_size, texture, font), title(titlee), topic(topicc) {}
    ~AboutScreen() = default;
    AboutScreen(AboutScreen& other) = delete;
    AboutScreen& operator=(AboutScreen& other) = delete;

    void runAboutScreen(sf::RenderWindow& about_window);
    void setTitle(TextFeatures& conf);
    void setTopic(TextFeatures& conf);

private:
    sf::Text title;
    sf::Text topic;
};