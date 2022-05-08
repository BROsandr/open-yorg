#include "Building/Wall.hpp"
#include "Building/Building.hpp"
#include "Game.hpp"

Wall::Wall(const FieldCoord &fieldCoord): Building(fieldCoord, 2, 1){
    text.setString("W");
    renderTexture.draw(text);
}

void Wall::draw(){
    Building::draw();
    renderTexture.display();
    Game::window->draw(*this);
}