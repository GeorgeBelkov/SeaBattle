#pragma once

#include <SFML/Graphics.hpp>
#include "AboutScreen.hpp"
#include "GameScreen.hpp"
#include "Screen.hpp"

constexpr static size_t MENU_MEMBERS = 4;                      // number of menu points
constexpr static int MENU_ITEMS_STEP_Y = 100;               // distance between points by Y 



class GameMenuScreen : public Screen
{
private:
    std::vector<sf::Text> points;
    int focused_item = 0;                // range from 0 to MENU_MEMBERS - 1. Provides info about current "active" point

public:
    GameMenuScreen(sf::Vector2f& desctop_size): Screen(desctop_size), points(MENU_MEMBERS) {}
    ~GameMenuScreen() = default;
    GameMenuScreen(GameMenuScreen& menu) = delete;
    GameMenuScreen& operator=(GameMenuScreen& menu) = delete;

    sf::Text operator[](size_t index) const { return points[index]; }                               // returns point of the menu
    int getFocusedItem() const { return focused_item; }

    void goToGameScreen(sf::RenderWindow& window, GameScreen& game) const { game.runGameLoop(window); }
    void goToAboutScreen(sf::RenderWindow& window, AboutScreen& about) const { about.runAboutScreen(window); }
    // void goToSettingsScreen(sf::RenderWindow& window, SettingsScreen& settings) const { settings.runSettingsScreen(window); }

    void createMenuItems();
    void chooseMenuItem(sf::Keyboard::Key key);
    void setMenuPosition(sf::Vector2f& position, int step);
};