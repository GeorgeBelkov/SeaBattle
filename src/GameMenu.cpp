#include "../include/GameMenu.hpp"


void GameMenu::loadFont(sf::String const& font_path)
{
    font.loadFromFile(font_path);
}


void GameMenu::createMenuItems()
{
    sf::String menu_items[MENU_MEMBERS] = { "New game", "Settings", "About game", "Exit" };
    points = new sf::Text[MENU_MEMBERS];

    int iter = 0;

    for(auto item : menu_items)
    {
        iter == 0 ? points[iter].setFillColor(sf::Color::Red) : points[iter].setFillColor(sf::Color::Black);
        points[iter].setString(item);
        points[iter].setCharacterSize(CARACTER_SIZE);
        points[iter].setFont(font);
        ++iter;
    }
}


void GameMenu::chooseMenuItem(sf::Keyboard::Key key)
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


void GameMenu::setMenuPosition(sf::Vector2f& position, int step)
{
    for (size_t i = 0; i < MENU_MEMBERS; i++)
    {
        points[i].setPosition(position.x, position.y + step * i);
        auto margin = points[i].sf::Text::getLocalBounds().width / 2.f;      //   shifting the menu points to make their centers on one line
        points[i].setPosition(position.x - margin, position.y + step * i);    
    }
}


void GameMenu::goToMenuPoint(sf::RenderWindow& window) const
{
    int index = 0;
    for (; index < MENU_MEMBERS; index++)
    {
        if (points[index].getFillColor() == sf::Color::Red)
            break;
    }

    switch (index)
    {
    case 0:
        // start_game();
        break;
    case 1:
        // settings();
        break;
    case 2:
        // about_game(window);
        break;
    case 3:
        window.close();
        break;
    
    default:
        break;
    }

    window.setTitle("SEA BATTLE");
    window.setMouseCursorVisible(false);
}


void GameMenu::createBackground(const sf::String img_path)
{
    texture_menu_window.loadFromFile(img_path);     // creating a background texture
    background.setTexture(&texture_menu_window);
}