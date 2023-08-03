#include "include/GameMenuScreen.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SEA BATTLE");
    window.setMouseCursorVisible(false);                                   // makes the mouse cursor invisible


    sf::Vector2f desctop_size(                                             // save desctop width and heigth
        sf::VideoMode::getDesktopMode().width,
        sf::VideoMode::getDesktopMode().height
    );


    sf::Texture texture;
    sf::Font font;
    GameMenuScreen menu(desctop_size, texture, font);
    
    menu.createBackground("images/backgrounds/main_menu.jpg");
    menu.loadFont("fonts/Wobblezz.ttf");
    menu.createMenuItems();


    sf::Vector2f menu_position(950.0, 200.0);
    menu.setMenuPosition(menu_position, MENU_ITEMS_STEP_Y);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
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