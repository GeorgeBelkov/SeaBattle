#pragma once

#include <list>
#include <memory>

#include <SFML/Graphics.hpp>

#include "AboutScreen.hpp"


// class Button


class Button
{
    
class ButtonMediator;
class ButtonSubject;
class ButtonObserver;

private:
    sf::RectangleShape borders;
    sf::Color background_color;
    sf::Text name;
    ButtonMediator* mediator;


    class ButtonSubject : public Subject {
    private:
        std::list<IObserver*> observers;
        ButtonMediator* mediator;

    public:
        explicit ButtonSubject(ButtonMediator* obj) : mediator(obj) {} 
        ~ButtonSubject() = default;
        void Notify() override;
        void Append(IObserver* obj) override;
        void Remove(IObserver* obj) override;

        std::list<IObserver*>& getObserversList() { return observers; }
    };


    // Mediator
    class ButtonMediator
    {
    private:
        ButtonSubject* on_click;
        ButtonSubject* on_pressed;
        Button* button;
        bool is_pressed = false;
    public:
        ButtonMediator(Button* btn): on_click(nullptr), on_pressed(nullptr), button(btn)
        {
            on_click = new ButtonSubject(btn->mediator);
            on_pressed = new ButtonSubject(btn->mediator);
        }
        ~ButtonMediator() { this->clear(); }

        void clear();

        bool getIsPressed() const { return is_pressed; }
        void setOnClick(ButtonSubject* on_click) { on_click = on_click; }
        void setOnPressed(ButtonSubject* on_pressed) { on_pressed = on_pressed; }
        ButtonSubject* getOnClick() { return on_click; }
        ButtonSubject* getOnPressed() { return on_pressed; }
        void setButton(Button* btn) { button = btn; }

        bool isCursorInButton(sf::Event::MouseButtonEvent& mouseCoords) const;

        void eventHandler(sf::Event& event, AboutScreen* const about);
    };


    class ButtonObserver : public IObserver
    {
    private:
        Button* btn;
    public:
        explicit ButtonObserver(Button* btn): btn(btn) {}
        ~ButtonObserver() override = default;
        void Update() override { btn->repaintingButton(); }
    };

public:

    Button(sf::RectangleShape borders, sf::Text name, sf::Color background_color)
        : borders(borders), background_color(background_color), name(name), mediator(new ButtonMediator(this))
    {
        this->borders.setFillColor(background_color);
        IObserver* back_btn = new ButtonObserver(this);   
        mediator->getOnClick()->Append(back_btn);
        mediator->getOnPressed()->Append(back_btn);
    }
    ~Button()
    {
        auto on_click_list = mediator->getOnClick()->getObserversList();
        auto on_pressed_list = mediator->getOnPressed()->getObserversList();
        for (auto observer : on_click_list)
        {
            delete observer;
            on_pressed_list.remove(observer);
        }
        for (auto observer : on_pressed_list)
        {
            if (observer == nullptr)
                continue;
            delete observer;
        }    
        delete mediator;
        mediator = nullptr;
    }
    void repaintingButton();
    
    void drawButton(sf::RenderWindow& window) const;
    
    void setTextPos(sf::Vector2f position) { name.setPosition(position); }
    void setPos(sf::Vector2f position) { borders.setPosition(position); }
    void setSize(sf::Vector2f size) { borders.setSize(size); }

    sf::Vector2f getTextPos() const { return name.getPosition(); }
    sf::Vector2f getPos() const { return borders.getPosition(); }
    sf::Vector2f getSize() const { return borders.getSize(); }
    ButtonMediator* getMediator() const { return mediator; }
};