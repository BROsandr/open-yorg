#include "Interface/BottomLayout.hpp"
#include "Interface/Button.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "ValuesAndTypes.hpp"
#include "Algorithms.hpp"
#include "Game.hpp"

BottomLayout::BottomLayout(){
	renderTexture.create(FIELD_LENGTH * CELL_LENGTH, 100);
	position = { 100, 800 - Layout::buttonSize.y - 50 } ;
	buttons.emplace_back( *this, "B" );
	buttons.emplace_back( *this, "C" );
}

void BottomLayout::tick(){
	Layout::tick();
	sf::Sprite sprite{renderTexture.getTexture()};
	sprite.setPosition(position);
    Game::window->draw(sprite);
}

sf::Vector2f BottomLayout::getNextDrawPos(){
    sf::Vector2f drawPos = nextDrawPos;
    nextDrawPos.x += buttonSize.x;
    return drawPos;
}