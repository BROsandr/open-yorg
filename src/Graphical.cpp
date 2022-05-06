#include <SFML/Graphics/Sprite.hpp>

#include "Graphical.hpp"
#include "ValuesAndTypes.hpp"
#include "Game.hpp"

Graphical::Graphical() {
	text.setFont(Game::font);
	text.setCharacterSize(CELL_WIDTH);
    setColor();
}

void Graphical::draw() {
}

void Graphical::setColor(sf::Color color){
    sf::Image image;
    image.create(CELL_LENGTH, CELL_WIDTH, color);
    backgroundTexture.loadFromImage(image);
    renderTexture.create(backgroundTexture.getSize().x, backgroundTexture.getSize().y);
    renderTexture.draw(sf::Sprite(backgroundTexture));
} 