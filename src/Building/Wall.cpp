#include "Building/Wall.hpp"
#include "Building/Building.hpp"
#include "Game.hpp"

Wall::Wall(const FieldCoord &fieldCoord): Building(fieldCoord, 2, 1){
    text.setString("W");
}

void Wall::draw(){
    Building::draw();
    Game::window->draw(*this);
}