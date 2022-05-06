#include "Game.hpp"
#include "ValuesAndTypes.hpp"

sf::RenderWindow *Game::window = nullptr;
int Game::crystals = 0;
sf::Font Game::font;

void Game::tick(){
    gameElements.tick();
    interface.update();
    interface.draw();
    // clock.tick()
}

Game::Game(sf::RenderWindow *const window) : input{ gameElements.field, 
                                                    interface, 
                                                    gameElements.field.pathSearchField, 
                                                    gameElements.enemies,
                                                    gameElements.bullets,
                                                    gameElements.damageCircles,
                                                    gameElements.resourceBalls,
                                                    gameElements.field.road
                                                  },
                                             interface { gameElements.field } {
    this->window = window;
    font.loadFromFile("resources/CascadiaCode.ttf");
}
