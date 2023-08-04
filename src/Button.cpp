#include "Button.hpp"


bool Button::isCursorInButton(sf::Event::MouseButtonEvent& mouseCoords) const
{
    return (mouseCoords.x <= (btn_pos.x + btn_size.x)) and (mouseCoords.y <= (btn_pos.y + btn_size.y));
}


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


void Button::drawButton(sf::RenderWindow& window) const
{
    window.draw(button_borders);
    window.draw(button_name);
}
