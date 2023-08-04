#pragma once

#include <SFML/Graphics.hpp>


class Button
{
public:
    Button(sf::RectangleShape btn, sf::Text btn_name, sf::Color btn_background, sf::Vector2f btn_pos, sf::Vector2f text_pos)
        : button_borders(btn), button_background_color(btn_background),
          button_name(btn_name), btn_size(button_borders.getSize()), btn_pos(btn_pos), text_pos(text_pos)
    {
        this->button_borders.setFillColor(button_background_color);
        this->button_name.setPosition(text_pos);
    }
    ~Button() = default;
    
    void repaintingBackButton();
    void drawButton(sf::RenderWindow& window) const;
    bool isCursorInButton(sf::Event::MouseButtonEvent& mouseCoords) const;
    
    void setIsPressed(bool newVal) { is_pressed = newVal; }                     // Get and Set is_pressed point
    bool getIsPressed() const { return is_pressed; }

    sf::Vector2f getButtonPos() const { return button_borders.getPosition(); }

private:
    sf::RectangleShape button_borders;
    sf::Color button_background_color;
    sf::Text button_name;
    sf::Vector2f btn_size;
    sf::Vector2f btn_pos;
    sf::Vector2f text_pos;
    bool is_pressed = false;
};