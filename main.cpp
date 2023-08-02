#include "include/GameMenu.hpp"


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
    GameMenu menu(desctop_size, texture, font);
    
    menu.create_background("images/backgrounds/main_menu.jpg");
    menu.load_font("fonts/Wobblezz.ttf");
    menu.create_menu_items();


    sf::Vector2f menu_position(950.0, 200.0);
    menu.set_menu_position(menu_position, MENU_ITEMS_STEP_Y);


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
                    menu.choose_menu_item(event.key.code);
                }
                if (event.key.code == sf::Keyboard::Key::Enter)
                    menu.go_to_menu_point(window);
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