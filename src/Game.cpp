#include "Game.hpp"
#include "ValuesAndTypes.hpp"

sf::RenderWindow *Game::window = nullptr;
sf::Font Game::font;

void Game::tick(){
    gameElements.tick();
    interface.update();
    interface.draw();
    clock.tick();
}

Game::Game(sf::RenderWindow *const window_) : input{ gameElements.field, interface, gameElements.field.pathSearchField, gameElements.enemies, gameElements.bullets, gameElements.damageCircles, gameElements.resourceBalls, gameElements.field.road }, interface { gameElements.field }, clock {gameElements.field.pathSearchField, gameElements.bullets, gameElements.damageCircles, gameElements.enemies} {
    srand(time(0));
    this->window = window_;
    font.loadFromFile("resources/CascadiaCode.ttf");
}
