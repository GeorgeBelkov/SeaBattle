#include "ButtonEventProcessor.hpp"


// ButtonMediator


void Button::ButtonMediator::eventHandler(sf::Event& event, AboutScreen* const about)
{
    if (event.type == sf::Event::MouseButtonPressed && !is_pressed &&
            event.mouseButton.button == sf::Mouse::Button::Left)
    {
        is_pressed = true;
        if (isCursorInButton(event.mouseButton))
            on_pressed->Notify();
    }
    if (event.type == sf::Event::MouseButtonReleased && is_pressed)
    {
        if (isCursorInButton(event.mouseButton))
        {
            // клик произошел
            is_pressed = false;
            on_click->Notify();
            about->getExiter()->Update();
        }
        is_pressed = false;
        on_released->Notify();  // Надо добавить subject on released.
    }
}


bool Button::ButtonMediator::isCursorInButton(sf::Event::MouseButtonEvent& mouseCoords) const
{
    return ((mouseCoords.x <= (button->getPos().x + button->getSize().x)) && (mouseCoords.y <= button->getPos().y + button->getSize().y));
}


void Button::ButtonMediator::clear()
{
    delete on_click;
    on_click = nullptr;
    delete on_pressed;
    on_pressed = nullptr;
    delete on_released;
    on_released = nullptr;
}


// ButtonSubject


void Button::ButtonSubject::Append(IObserver* obj) { observers.push_back(obj); }

void Button::ButtonSubject::Remove(IObserver* obj) { observers.remove(obj); }

void Button::ButtonSubject::Notify()
{
    for (auto observer : observers)
        observer->Update();
}


// Button


void Button::drawButton(sf::RenderWindow& window) const
{
    window.draw(borders);
    window.draw(name);
}


void Button::repaintingButton()
{
    if (mediator->getIsPressed())
    {
        name.setFillColor(sf::Color::Blue);
        return;
    }
    name.setFillColor(sf::Color::White);
    return;
}