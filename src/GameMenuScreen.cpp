#include "GameMenuScreen.hpp"
#include <array>

// Represents Main menu
void GameMenuScreen::createMenuItems()
{
    std::array<sf::String, MENU_MEMBERS> menu_items = { "New game", "Settings", "About game", "Exit" };
    int iter = 0;

    for(auto item : menu_items)
    {
        iter == 0 ? points[iter].setFillColor(sf::Color::Red) : points[iter].setFillColor(sf::Color::Black);
        points[iter].setString(item);
        points[iter].setCharacterSize(CHARACTER_SIZE);
        points[iter].setFont(font);
        ++iter;
    }
}


void GameMenuScreen::chooseMenuItem(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Key::Up:
        if (focused_item == 0)
        {
            points[focused_item].setFillColor(sf::Color::Black);
            focused_item = MENU_MEMBERS - 1;
            points[focused_item].setFillColor(sf::Color::Red);
        }
        else
        {
            points[focused_item--].setFillColor(sf::Color::Black);
            points[focused_item].setFillColor(sf::Color::Red);
        }
        break;
    
    case sf::Keyboard::Key::Down:
        if (focused_item == MENU_MEMBERS - 1)
        {
            points[focused_item].setFillColor(sf::Color::Black);
            focused_item = 0;
            points[focused_item].setFillColor(sf::Color::Red);
        }
        else
        {
            points[focused_item++].setFillColor(sf::Color::Black);
            points[focused_item].setFillColor(sf::Color::Red);
        }
        break;
    }
}


void GameMenuScreen::setMenuPosition(sf::Vector2f& position, int step)
{
    for (auto i = 0; i < MENU_MEMBERS; i++)
    {
        points[i].setPosition(position.x, position.y + step * i);
        auto margin = points[i].sf::Text::getLocalBounds().width / 2.f;      //   shifting the menu points to make their centers on one line
        points[i].setPosition(position.x - margin, position.y + step * i);    
    }
}