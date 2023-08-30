#include "AboutScreen.hpp"
#include "ButtonEventProcessor.hpp"


void AboutScreen::runAboutScreen(sf::RenderWindow& about_window)
{
    about_window.setTitle("About");
    about_window.setMouseCursorVisible(true);
    
    sf::Vector2f desctop_size(                                             // we can use background.getSize() and define desctop_size var only once ?
        sf::VideoMode::getDesktopMode().width,
        sf::VideoMode::getDesktopMode().height
    );

    sf::RectangleShape bg(sf::Vector2f(70.0, 50.0));
    sf::Text text("Back", font);
    
    
    auto back_button = std::make_unique<Button>(bg, text, sf::Color::Black);
    back_button->setPos(sf::Vector2f(0.0, 0.0));
    back_button->setTextPos(sf::Vector2f(10.0, 5.0));

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
            
            back_button->getMediator()->eventHandlerForAboutScreen(event, this);


            if (this->getExiter()->get_flag())
            {
                this->getExiter()->set_flag(false);
                return;
            }
        }
        about_window.clear(sf::Color::White);

        about_window.draw(background);
        about_window.draw(title);
        about_window.draw(topic);
        back_button->drawButton(about_window);

        about_window.display();
    }
}


void AboutScreen::setTitle(sf::Color const color)
{
    title.setStyle(sf::Text::Style::Bold);
    title.setPosition(sf::Vector2f(700.0, 300.0));
    title.setFillColor(color);
}


void AboutScreen::setTopic(sf::Color const color)
{
    sf::FloatRect titleSize = title.getLocalBounds();
    topic.setPosition(
        sf::Vector2f(title.getPosition().x - titleSize.width / 1.8, title.getPosition().y + titleSize.height * 2)
    );
    topic.setFillColor(color);
}