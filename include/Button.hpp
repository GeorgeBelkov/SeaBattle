#pragma once

#include <SFML/Graphics.hpp>


// Represents button entity. Can be placed in different parts of window.
class Button
{
private:
    sf::RectangleShape borders;
    sf::Color background_color;
    sf::Text name;
    sf::Vector2f size;
    sf::Vector2f pos;
    sf::Vector2f text_pos;
    bool is_pressed = false;

public:
    Button(sf::RectangleShape borders, sf::Text name, sf::Color background_color, sf::Vector2f btn_pos, sf::Vector2f text_pos)
        : borders(borders), background_color(background_color), name(name), size(borders.getSize()), pos(btn_pos), text_pos(text_pos)
    {
        this->borders.setFillColor(background_color);
        this->name.setPosition(text_pos);
    }
    ~Button() = default;
    
    void repaintingBackButton();
    void drawButton(sf::RenderWindow& window) const;
    bool isCursorInButton(sf::Event::MouseButtonEvent& mouseCoords) const;
    
    void setIsPressed(bool newVal) { is_pressed = newVal; }                     // Get and Set is_pressed point
    bool getIsPressed() const { return is_pressed; }

    sf::Vector2f getButtonPos() const { return borders.getPosition(); }
};