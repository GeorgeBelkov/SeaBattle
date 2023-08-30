#include <string_view>
#include <string>

#include "include/GameMenuScreen.hpp"
#include "include/AboutScreen.hpp"
#include "include/GameScreen.hpp"


constexpr std::string_view screen_topic(
    "The game is based on the SFML graphics library. There is no single player mode.\n"    \
    "  The game can be played with friends. The player performing the move makes a  \n"    \    
    "shot - presses on the cell in which, in his opinion, the enemy ship is located,\n"    \
    " for example, B1. If the shot landed in a cell not occupied by any enemy ship, \n"    \  
    " then ... the opponents turn comes, and a blow will be displayed on opponents  \n"    \   
    "    square in this place. The game continues until one of the players hits     \n"    \       
    "                      all the enemy ships.                                       "    \
);



inline void loadFontFromFile(std::filesystem::path const& font_path, sf::Font& font)
{
    font.loadFromFile(font_path);
}


inline void loadTextureFromFile(std::filesystem::path const& img_path, sf::Texture& texture)
{
    texture.loadFromFile(img_path);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SEA BATTLE");
    window.setMouseCursorVisible(false);                                      // makes the mouse cursor invisible


    sf::Vector2f desctop_size(                                                // save desctop width and heigth
        sf::VideoMode::getDesktopMode().width,
        sf::VideoMode::getDesktopMode().height
    );
 
    sf::Texture texture;
    loadTextureFromFile("images/backgrounds/main_menu.jpg", texture);
    sf::Font font;
    loadFontFromFile("fonts/Wobblezz.ttf", font);

    GameMenuScreen menu(desctop_size);                                       // create GameMenu obj and set data
    
    menu.setFont(font);
    menu.setTexture(texture);
    menu.setBackground();
    menu.createMenuItems();

    sf::Vector2f menu_position(950.0, 200.0);                                // Text position on the screen
    menu.setMenuPosition(menu_position, MENU_ITEMS_STEP_Y);


    ////////////////////////////////////////////////////////////////////


    sf::String screen_title = "ABOUT GAME";

    AboutScreen about(desctop_size, screen_title, static_cast<std::string>(screen_topic));

    loadTextureFromFile("images/backgrounds/about.jpg", texture);
    loadFontFromFile("fonts/Marlboro.ttf", font);

    about.setFont(font);
    about.setTexture(texture);
    about.setBackground();
    about.setTitle(sf::Color::Black);
    about.setTopic(sf::Color::Black);


    ///////////////////////////////////////////////////////////////////////

    // sf::RectangleShape bg(sf::Vector2f(285.0, 115.0));
    // sf::Text text("START", font, 36);
    
    
    // auto start_button = std::make_unique<Button>(bg, text, sf::Color(204, 102, 0));
    // start_button->setPos(sf::Vector2f(815.0, 93.0));
    // start_button->setTextPos(sf::Vector2f(875, 129));

    GameScreen game(desctop_size);
    loadTextureFromFile("images/backgrounds/game.jpg", texture);
    game.setTexture(texture);
    game.setFont(font);
    game.setBackground();


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
                            menu.goToGameScreen(window, game);
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