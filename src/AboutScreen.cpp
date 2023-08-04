#include "AboutScreen.hpp"
#include "Button.hpp"


void AboutScreen::runAboutScreen(sf::RenderWindow& about_window)
{
    about_window.setTitle("About");
    about_window.setMouseCursorVisible(true);
    
    sf::Vector2f desctop_size(                                             // save desctop width and heigth
        sf::VideoMode::getDesktopMode().width,
        sf::VideoMode::getDesktopMode().height
    );

    sf::RectangleShape bg(sf::Vector2f(70, 50.0));
    sf::Text text("Back", font);

    Button back_button(bg, text, sf::Color::Black, sf::Vector2f(0.0, 0.0), sf::Vector2f(10.0, 5.0));
    
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
                if (back_button.isCursorInButton(event.mouseButton))
                    back_button.repaintingBackButton();
            }
            if (event.type == sf::Event::MouseButtonReleased and back_button.getIsPressed())
            {
                if (back_button.isCursorInButton(event.mouseButton))
                {
                    back_button.setIsPressed(false);
                    return;
                }
                back_button.setIsPressed(false);
                back_button.repaintingBackButton();
            }
                
        }
        about_window.clear(sf::Color::White);

        about_window.draw(background);
        about_window.draw(title);
        about_window.draw(topic);
        back_button.drawButton(about_window);
        about_window.display();
    }
}


void AboutScreen::setTitle(TextFeatures& conf)
{
    title.setString(conf.text);
    title.setFont(font);
    title.setCharacterSize(conf.characterSize);
    title.setStyle(sf::Text::Style::Bold);
    title.setFillColor(conf.color);
    title.setPosition(sf::Vector2f(700.0, 300.0));
}


void AboutScreen::setTopic(TextFeatures& conf)
{
    topic.setString(conf.text);
    topic.setFont(font);
    topic.setCharacterSize(conf.characterSize);
    sf::FloatRect titleSize = title.getLocalBounds();
    topic.setPosition(
        sf::Vector2f(title.getPosition().x - titleSize.width / 1.8, title.getPosition().y + titleSize.height * 2)
    );
    topic.setFillColor(conf.color);
}