#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "AboutScreen.hpp"

constexpr int MENU_MEMBERS = 4;             // number of menu points
constexpr int CARACTER_SIZE = 100;          // font size
constexpr int MENU_ITEMS_STEP_Y = 100;      // distance between points by Y 


class GameMenuScreen : public Screen
{
public:
    GameMenuScreen(sf::Vector2f& desctop_size, sf::Texture texture, sf::Font font)
        : Screen(desctop_size, texture, font), points(nullptr) {}
    ~GameMenuScreen() { delete[] points; }
    GameMenuScreen(GameMenuScreen& menu) = delete;
    GameMenuScreen& operator=(GameMenuScreen& menu) = delete;

    sf::Text operator[](size_t index) const { return points[index]; }                               // returns point of the menu
    int getFocusedItem() const { return focused_item; }

    void goToAboutScreen(sf::RenderWindow& window, AboutScreen& about) const { about.aboutGame(window); }
    // void goToSettingsScreen(sf::RenderWindow& window, SettingsScreen& settings) const { settings.game_config(window, settings); }
    // void goToGameScreen(sf::RenderWindow& window, GameScreen& game) const { game.run_game(window, game); }

    void createMenuItems();
    void chooseMenuItem(sf::Keyboard::Key key);
    void setMenuPosition(sf::Vector2f& position, int step);

private:
    sf::Text* points;
    int focused_item = 0;                // range from 0 to MENU_MEMBERS - 1. Provides info about current "active" point
};