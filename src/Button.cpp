#include "Button.hpp"


void Button::repaintingBackButton()
{
    if (is_pressed)
    {
        button_name.setFillColor(sf::Color::Blue);
        return;
    }
    button_name.setFillColor(sf::Color::White);
    return;
}


void Button::drawButton(sf::RenderWindow& window)
{
    window.draw(button);
    window.draw(button_name);
}
    