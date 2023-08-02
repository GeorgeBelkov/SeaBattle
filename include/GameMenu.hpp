#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.hpp"

constexpr int MENU_MEMBERS = 4;
constexpr int CARACTER_SIZE = 100;
constexpr int MENU_ITEMS_STEP_Y = 100;


static int focused_item = 0;
static bool is_pressed = false;


class GameMenu : public Screen
{
public:
    GameMenu(sf::Vector2f& desctop_size, sf::Texture texture, sf::Font font)
        : Screen(desctop_size, texture, font), points(nullptr) {}
    ~GameMenu() { delete[] points; }
    
    sf::Text operator[](size_t index) const { return points[index]; }                               // return point of the menu
    
    void goToMenuPoint(sf::RenderWindow& window) const;

    void createMenuItems();
    void chooseMenuItem(sf::Keyboard::Key key);
    void setMenuPosition(sf::Vector2f& position, int step);

private:
    GameMenu(GameMenu& menu);
    GameMenu& operator=(GameMenu& menu);

    sf::Text* points;
};