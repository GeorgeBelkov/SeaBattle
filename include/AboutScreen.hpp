#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "IObserver.hpp"


// Represents About Screen (Game menu -> About game)
class AboutScreen : public Screen
{
private:

    class Exiter : public IObserver {
    protected:
        bool exit_flag = false;
    public:
        Exiter() = default;
        void Update() override
        {
            exit_flag = true;
        }
        bool get_flag() const { return exit_flag; }
        void set_flag(bool flag) { exit_flag = flag; }
    };

    sf::Text title;
    sf::Text topic;
    Exiter* exit_flag;

public:
    AboutScreen(sf::Vector2f& desctop_size, sf::String title, sf::String topic)
        : Screen(desctop_size),
          title(sf::Text(title, font, CHARACTER_SIZE)),
          topic(sf::Text(topic, font, CHARACTER_SIZE / 3)),
          exit_flag(new Exiter()) {}
          
    ~AboutScreen()
    {
        delete exit_flag;
        exit_flag = nullptr;
    }
    AboutScreen(AboutScreen& other) = delete;
    AboutScreen& operator=(AboutScreen& other) = delete;

    Exiter* getExiter() const { return exit_flag; }
    void runAboutScreen(sf::RenderWindow& about_window);
    void setTitle(sf::Color color);
    void setTopic(sf::Color color);
};