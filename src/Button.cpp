#include "Button.hpp"


bool Button::isCursorInButton(sf::Event::MouseButtonEvent& mouseCoords) const
{
    return (mouseCoords.x <= (pos.x + size.x)) and (mouseCoords.y <= (pos.y + size.y));
}


void Button::repaintingBackButton()
{
    if (is_pressed)
    {
        name.setFillColor(sf::Color::Blue);
        return;
    }
    name.setFillColor(sf::Color::White);
    return;
}


void Button::drawButton(sf::RenderWindow& window) const
{
    window.draw(borders);
    window.draw(name);
}
