#include "Interface/BottomLayout.hpp"
#include "Interface/Button.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "ValuesAndTypes.hpp"
#include "Algorithms.hpp"
#include "Game.hpp"

BottomLayout::BottomLayout(){
	buttons.emplace_back(*this);
	renderTexture.create(FIELD_LENGTH * CELL_LENGTH, 100);
}

void BottomLayout::tick(){
	Layout::tick();
	sf::Sprite sprite{renderTexture.getTexture()};
	sprite.setPosition(0, Algorithms::getFieldSize().y - Layout::buttonSize.y);
    Game::window->draw(sprite);
}