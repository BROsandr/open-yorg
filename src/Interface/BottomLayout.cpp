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
	sprite.setPosition(100, Game::window->getSize().y - Layout::buttonSize.y - 50);
    Game::window->draw(sprite);
}