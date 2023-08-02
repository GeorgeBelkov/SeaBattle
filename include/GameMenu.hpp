#pragma once

#include <SFML/Graphics.hpp>

#define MENU_MEMBERS 4
#define CARACTER_SIZE 100
#define MENU_ITEMS_STEP_Y 100


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
    void go_to_menu_point(sf::RenderWindow& window) const;

    void create_menu_items();
    void load_font(sf::String const& font_path);
    void choose_menu_item(sf::Keyboard::Key key);
    void set_menu_position(sf::Vector2f& position, int step);
    void create_background(const sf::String img_path);

private:
    GameMenu(GameMenu& menu);
    GameMenu& operator=(GameMenu& menu);

    sf::RectangleShape background;
    sf::Texture texture_menu_window;
    sf::Font font;
    sf::Text* points;
};