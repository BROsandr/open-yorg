#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Input.hpp"
#include "GameElements.hpp"
#include "Interface.hpp"
#include "Clock.hpp"

class Game{
public:
    GameElements gameElements;
    Input input;
    static sf::RenderWindow *window;
    Interface interface;
    Clock clock;
    static sf::Font font;

    Game(sf::RenderWindow *const renderWindow);
    void tick();

private:
    void draw();
    void update();
};




