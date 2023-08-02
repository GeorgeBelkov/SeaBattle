#pragma once

#include <SFML/Graphics.hpp>

constexpr int MENU_MEMBERS = 4;
constexpr int CARACTER_SIZE = 100;
constexpr int MENU_ITEMS_STEP_Y = 100;


static int focused_item = 0;
static bool is_pressed = false;


class GameMenu
{
public:
    GameMenu(sf::Vector2f& desctop_size, sf::Texture texture, sf::Font font)
        : background(desctop_size), texture_menu_window(texture), font(font), points(nullptr) {}
    ~GameMenu() { delete[] points; }
    
    sf::Text operator[](size_t index) const { return points[index]; }
    sf::RectangleShape getBackground() const { return background; }
    void goToMenuPoint(sf::RenderWindow& window) const;

    void createMenuItems();
    void loadFont(sf::String const& font_path);
    void chooseMenuItem(sf::Keyboard::Key key);
    void setMenuPosition(sf::Vector2f& position, int step);
    void createBackground(const sf::String img_path);

private:
    GameMenu(GameMenu& menu);
    GameMenu& operator=(GameMenu& menu);

    sf::RectangleShape background;
    sf::Texture texture_menu_window;
    sf::Font font;
    sf::Text* points;
};