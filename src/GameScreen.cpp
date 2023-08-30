#include "GameScreen.hpp"


void GameScreen::drawField(sf::RenderWindow& window, sf::RectangleShape& bdrs, Field* field)
{
    int top = field->getTop(), left = field->getLeft();
    for (size_t i = 0, CELLS_IN_COLUMN = CELLS_IN_ROW; i < CELLS_IN_ROW; i++)
    {
        for (size_t j = 0; j < CELLS_IN_COLUMN; j++)
        {
            auto cell = field->getField()[CELLS_IN_ROW * i + j];
            bdrs.setPosition(left + j * 57, top + i * 57);
            switch (cell)
            {
            case Cell::EMPTY:
                break;
            case Cell::SHIP:
                bdrs.setTexture(&images.getImgStorage()["ship"]);
                window.draw(bdrs);
                break;
            case Cell::POINT:
                bdrs.setTexture(&images.getImgStorage()["point"]);
                window.draw(bdrs);
                break;
            case Cell::HIT:
                bdrs.setTexture(&images.getImgStorage()["hit"]);
                window.draw(bdrs);
                break;
            case Cell::MISS:
                bdrs.setTexture(&images.getImgStorage()["miss"]);
                window.draw(bdrs);
                break;
            default:
                break;
            }
        }
    }  
}


void GameScreen::runGameLoop(sf::RenderWindow& game_window)
{
    game_window.setTitle("Game");
    game_window.setMouseCursorVisible(true);
    
    sf::Vector2f desctop_size(                                             // we can use background.getSize() and define desctop_size var only once ?
        sf::VideoMode::getDesktopMode().width,
        sf::VideoMode::getDesktopMode().height
    );
    sf::RectangleShape bdrs(sf::Vector2f(57, 57));

    sf::RectangleShape bg(sf::Vector2f(285.0, 115.0));
    sf::Text text("Start", font, 72);

    auto start_button = std::make_unique<Button>(bg, text, sf::Color(204, 102, 0));
    start_button->setPos(sf::Vector2f(815.0, 93.0));
    start_button->setTextPos(sf::Vector2f(892, 100));

    mediator->setStartButton(start_button.get());

    // run the program as long as the window is open
    while (game_window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (game_window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                game_window.close();

            this->mediator->eventHandler(event);

            if (players_field->getShipsPlaced() && mediator->getGameState() == GameState::PLACING_SHIPS)
                this->mediator->getStartButton()->getMediator()->eventHandlerForGameScreen(event, this);
            
            if (this->loader->getFlag())
            {
                this->startGame(game_window);
                this->loader->setFlag(false);
                // TODO: Продумать логику выхода обратно в меню.
            }
        }

        game_window.clear();
        game_window.draw(background);
        if (players_field->getShipsPlaced() && mediator->getGameState() == GameState::PLACING_SHIPS)
            mediator->getStartButton()->drawButton(game_window);
        drawField(game_window, bdrs, players_field.get());
        drawField(game_window, bdrs, enemyes_field.get());
        game_window.display();
    }
}


void GameScreen::GameScreenMediator::eventHandler(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && !mouse_is_pressed &&
            event.mouseButton.button == sf::Mouse::Button::Left)
    {
        mouse_is_pressed = true;
    }
    if (event.type == sf::Event::MouseButtonReleased && mouse_is_pressed &&
            event.mouseButton.button == sf::Mouse::Button::Left)
    {
        if (game_state == GameState::ENEMY_STEP)
        {
            // TODO: получаем данные с сервера.
        }
        else
        {
            if (game_state == GameState::PLACING_SHIPS &&
                game->getPlayersField()->isClickOnMyField(event.mouseButton))
            {
                game->getPlayersField()->onClick(game->getPlayersField()->convertToCellId(event.mouseButton));
            }

            else if (game_state == GameState::PLAYER_STEP &&
                    game->getEnemyesField()->isClickOnMyField(event.mouseButton))
            {
                game->getEnemyesField()->onClick(game->getEnemyesField()->convertToCellId(event.mouseButton));
            }

        }
        mouse_is_pressed = false;
    }
}


void GameScreen::startGame(sf::RenderWindow& game_window)
{
    std::cout << "Game starts now!\n";
}