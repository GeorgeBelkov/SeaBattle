#include "include/GameMenuScreen.hpp"
#include "include/AboutScreen.hpp"


static sf::String topic(
    "The game is based on the SFML graphics library. There is no single player mode.\n"    \
    "  The game can be played with friends. The player performing the move makes a  \n"    \    
    "shot - presses on the cell in which, in his opinion, the enemy ship is located,\n"    \
    " for example, B1. If the shot landed in a cell not occupied by any enemy ship, \n"    \  
    " then ... the opponents turn comes, and a blow will be displayed on opponents  \n"    \   
    "    square in this place. The game continues until one of the players hits     \n"    \       
    "                      all the enemy ships.                                       "    \
);


int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SEA BATTLE");
    window.setMouseCursorVisible(false);                                      // makes the mouse cursor invisible


    sf::Vector2f desctop_size(                                                // save desctop width and heigth
        sf::VideoMode::getDesktopMode().width,
        sf::VideoMode::getDesktopMode().height
    );
    sf::Texture texture;
    sf::Font font;
    sf::Text text;

    GameMenuScreen menu(desctop_size, texture, font);                      // create GameMenu obj and set data
    
    menu.createBackground("images/backgrounds/main_menu.jpg");
    menu.loadFont("fonts/Wobblezz.ttf");
    menu.createMenuItems();

    sf::Vector2f menu_position(950.0, 200.0);                              // Text position on the screen
    menu.setMenuPosition(menu_position, MENU_ITEMS_STEP_Y);

    AboutScreen about(desctop_size, texture, font, text, text);

    about.createBackground("images/backgrounds/about.jpg");
    about.loadFont("fonts/Marlboro.ttf");
    TextFeatures title_features(CARACTER_SIZE, sf::String(L"ABOUT GAME"));
    TextFeatures topic_features(CARACTER_SIZE / 3, topic);
    about.setTitle(title_features);
    about.setTopic(topic_features);


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Key::Up || 
                    event.key.code == sf::Keyboard::Key::Down)
                {
                    menu.chooseMenuItem(event.key.code);
                }
                if (event.key.code == sf::Keyboard::Key::Enter)
                {
                    switch (menu.getFocusedItem())
                    {
                        case 0:
                            // menu.goToGameScreen();
                            break;
                        case 1:
                            // menu.goToSettingsScreen();
                            break;
                        case 2:
                            menu.goToAboutScreen(window, about);
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
            }
            
        }
        // clear the window with black color
        window.clear();

        // draw everything here...
        window.draw(menu.getBackground());

        for (size_t i = 0; i < MENU_MEMBERS; i++)                       // drawing menu
            window.draw(menu[i]);
        

        // end the current frame
        window.display();
    }

    return 0;
}