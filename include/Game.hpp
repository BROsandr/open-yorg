#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Input/Input.hpp"
#include "GameElements.hpp"
#include "Interface/Interface.hpp"
#include "GameClock.hpp"

class Game{
public:
    GameElements gameElements;
    Input input;
    static sf::RenderWindow *window;
    Interface interface;
    GameClock clock;
    static sf::Font font;

    Game(sf::RenderWindow *const renderWindow);
    void tick();

private:
    void draw();
    void update();
};




