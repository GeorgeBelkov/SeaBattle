#pragma once


#include <SFML/Graphics.hpp>


class Button
{
public:
    Button(sf::RectangleShape btn, sf::Text btn_name, sf::Color btn_background, sf::Vector2f btn_pos, sf::Vector2f text_pos)
        : button(btn), button_name(btn_name), button_background_color(btn_background), button_size(button.getSize())
    {
        button.setPosition(btn_pos);
        button.setFillColor(button_background_color);
        button_name.setPosition(text_pos);
    }
    ~Button() = default;
    
    void repaintingBackButton();
    void drawButton(sf::RenderWindow& window);
    
    void setIsPressed(bool temp) { is_pressed = temp; }
    bool getIsPressed() const { return is_pressed; }
    sf::Vector2f getButtonPos() const { return button.getPosition(); }

private:
    sf::RectangleShape button;
    sf::Text button_name;
    sf::Color button_background_color;
    sf::Vector2f button_size;
    bool is_pressed = false;
};
