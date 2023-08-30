#pragma once

#include <list>
#include <array>
#include <string>
#include <memory>
#include <iostream>
#include <filesystem>
#include <unordered_map>


#include <SFML/Graphics.hpp>

#include "Screen.hpp"
#include "IObserver.hpp"
#include "ButtonEventProcessor.hpp"


constexpr static int TOP_PX = 322;
constexpr static int PLAYERS_LEFT_PX = 301;
constexpr static int ENEMYES_LEFT_PX = 1044;
constexpr static int WIDTH = 570;
constexpr static int CELLS_IN_ROW = 10;


////////////////GAME_STATE////////////////////


enum class GameState {
    PLACING_SHIPS = 0,
    PLAYER_STEP,
    ENEMY_STEP
};


////////////////GAME_SCREEN////////////////////

class Button;

class GameScreen : public Screen
{
private:

    class GameScreenMediator;

    enum class Cell {
        EMPTY = 0,
        MISS,
        SHIP,
        POINT,
        HIT
    };

    ////////////////GameScreenMediator///////////////////


    class GameScreenMediator
    {
    private:
        GameScreen* game;
        Button* start_btn;
        bool mouse_is_pressed = false;
        GameState game_state = GameState::PLACING_SHIPS;
    public:
        explicit GameScreenMediator(GameScreen* game): 
            game(game), start_btn(nullptr) {}
        ~GameScreenMediator() = default;

        GameState getGameState() const { return game_state; }
        Button* getStartButton() { return start_btn; }

        void setStartButton(Button* btn) { start_btn = btn; }

        void eventHandler(sf::Event& event);
    };


    ////////////////GameLoader//////////////////


    class GameLoader : public IObserver
    {
    private:
        bool game_starts = false;
    public:
        GameLoader() = default;
        ~GameLoader() override = default;
        void Update() override { game_starts = true; }
        bool getFlag() const { return game_starts; }
        void setFlag(bool flag) { game_starts = flag; }
    };


    ////////////////GAME_FIELD_IMAGES////////////////////


    class GameFieldImages
    {
    private:
        std::unordered_map<std::string, sf::Texture> images;
    public:
        GameFieldImages()
        {
            sf::Texture texture;
            texture.loadFromFile("images/game/ship.png");
            images.insert({"ship", texture});
            texture.loadFromFile("images/game/point.png");
            images.insert({"point", texture});
            texture.loadFromFile("images/game/hit.png");
            images.insert({"hit", texture});
            texture.loadFromFile("images/game/miss.png");
            images.insert({"miss", texture});
        }
        ~GameFieldImages() = default;
        std::unordered_map<std::string, sf::Texture>& getImgStorage() { return images; }
    };


    ////////////////FIELD////////////////////

    // BASE class. Represents the players and enemyes field on game screen.
    class Field
    {
    protected:
        int top, left, width;
        bool ships_placed = false;
        std::array<Cell, 100> field = {Cell::EMPTY};
    public:
        
        Field(int left_px): top(TOP_PX), left(left_px), width(WIDTH) { }

        std::pair<int, int> convertToCellId(sf::Event::MouseButtonEvent& click_coords)
        {
            int i = (click_coords.y - top) / (width / 10);
            int j = (click_coords.x - left) / (width / 10);
            return std::make_pair(i, j);
        }
        bool isClickOnMyField(sf::Event::MouseButtonEvent& click_coords)
        {
            return ((click_coords.x <= (left + width)) && (click_coords.x >= left) &&
                    (click_coords.y <= (top + width)) && (click_coords.y >= top));
        }

        std::array<Cell, 100>& getField() { return field; }
        int getTop() const { return top; }
        int getLeft() const { return left; }
        bool getShipsPlaced() const { return ships_placed; }

        virtual ~Field() = default;
        virtual void onClick(std::pair<int, int> cell) = 0;
    };


    class MyField : public Field
    {
    public:
        MyField(): Field(PLAYERS_LEFT_PX) {}
        ~MyField() = default;
        void onClick(std::pair<int, int> cell) override
        {
            // std::cout << "(i: " << cell.first << ", j: " << cell.second << ")\n";
            static int filled_cells = 0;                                                            // filled_cells == 20   ==>   ships are placed, we can start 
            if (ships_placed)
                return;
            if (!ships_placed &&
                field[CELLS_IN_ROW * cell.first + cell.second] == Cell::EMPTY)
            {
                field[CELLS_IN_ROW * cell.first + cell.second] = Cell::SHIP;
                filled_cells++;
            }
            // std::cout << "filled cells: " << filled_cells << "\n";
            if (filled_cells == 20)
                ships_placed = true;
        }
    };


    class EnemyField : public Field
    {
    public:
        ~EnemyField() = default;
        EnemyField(): Field(ENEMYES_LEFT_PX) {}
        void setEnemyShips(char* enemy_field)
        {
            for (size_t i = 0; i < 100; i++)
            {
                if (enemy_field[i] == '1')
                    field[i] = Cell::SHIP;
            }
        }
        void onClick(std::pair<int, int> cell) override
        {
            // TODO: Логика нажатия игроком на поле соперника.
        }
    };


    // atributes
    std::unique_ptr<Field> players_field;
    std::unique_ptr<Field> enemyes_field;
    GameScreenMediator* mediator;
    GameFieldImages images;
    GameLoader* loader;

public:

    GameScreen(sf::Vector2f& desctop_size):
        Screen(desctop_size),
        players_field(new MyField()),
        enemyes_field(new EnemyField()),
        mediator(new GameScreenMediator(this)),
        loader(new GameLoader())
    { }
    
    ~GameScreen()
    {
        // auto observers = mediator->getOnShipsPlaced()->getObserversList();
        // for (auto observer : observers)
        //     delete observer;
        
        delete mediator;
        delete loader;
    }

    std::unique_ptr<Field>& getPlayersField() { return players_field; }
    std::unique_ptr<Field>& getEnemyesField() { return enemyes_field; }

    void runGameLoop(sf::RenderWindow& game_window);
    void startGame(sf::RenderWindow& game_window);


    void drawField(sf::RenderWindow& window, sf::RectangleShape& bdrs, Field* field);
    GameScreenMediator* getMediator() { return mediator; }

    GameLoader* getGameLoader() { return loader; }
};