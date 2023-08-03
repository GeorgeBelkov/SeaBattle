#include "AboutScreen.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>


void AboutScreen::aboutScreenDraw(sf::RenderWindow& about_window)
{
    about_window.draw(background);
}


void AboutScreen::aboutGame(sf::RenderWindow& about_window)
{
    about_window.setTitle("About");
    about_window.setMouseCursorVisible(true);
    
    sf::Vector2f desctop_size(                                             // save desctop width and heigth
        sf::VideoMode::getDesktopMode().width,
        sf::VideoMode::getDesktopMode().height
    );

    sf::String description = (
        "Hi! It's the mulyiplayer game - SeaBattle\nThere are some simple rules:\n" \
        "1) You must ....\n 2) You ..."                                             \
    );
    sf::Text text_about(description, font, 32);
    sf::Vector2f text_pos(700.0, 200.0);
    text_about.setPosition(text_pos);
    
    sf::RectangleShape btn(sf::Vector2f(70, 50.0));
    sf::Text btn_text("Back", font);

    Button back_button(btn, btn_text, sf::Color::Black, sf::Vector2f(0.0, 0.0), sf::Vector2f(10.0, 5.0));


    sf::Vector2f button_pos = back_button.getButtonPos();
    // run the program as long as the window is open
    while (about_window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (about_window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                about_window.close();
            if (event.type == sf::Event::MouseButtonPressed and !back_button.getIsPressed() and
                event.mouseButton.button == sf::Mouse::Button::Left)
            {
                back_button.setIsPressed(true);
                if ((event.mouseButton.x <= button_pos.x) and (event.mouseButton.y <= button_pos.y))
                    back_button.repaintingBackButton();
            }
            if (event.type == sf::Event::MouseButtonReleased and back_button.getIsPressed())
            {
                if ((event.mouseButton.x <= button_pos.x) and (event.mouseButton.y <= button_pos.y))
                {
                    back_button.setIsPressed(false);
                    return;
                }
                back_button.setIsPressed(false);
                back_button.repaintingBackButton();
            }
                
        }
        about_window.clear(sf::Color::White);

        aboutScreenDraw(about_window);
        back_button.drawButton(about_window);
        about_window.draw(text_about);

        about_window.display();
    }
}