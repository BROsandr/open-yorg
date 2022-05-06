#include "Can/CanStore.hpp"
#include "Building/Building.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include "Game.hpp"
#include "ValuesAndTypes.hpp"
#include <string>

CanStore::CanStore(const FieldCoord &fieldCoord, int connectionRadius): Building(fieldCoord, connectionRadius){
	storageText.setFont(Game::font);
	storageText.setCharacterSize(15);
    storageText.setPosition(getPosition() - sf::Vector2f{10, 10});
    storageText.setFillColor(sf::Color::Black);
}

void CanStore::draw(){
    Building::draw();
    Game::window->draw(storageText);
}


void CanStore::update(){
    Building::update();
    storageText.setString(std::to_string(storage));
}


