#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Graphical.hpp"
#include "ValuesAndTypes.hpp"
#include "Game.hpp"

Graphical::Graphical() {
	text.setFont(Game::font);
	text.setCharacterSize(CELL_WIDTH);
    setColor();
    renderTexture.create(backgroundTexture.getSize().x, backgroundTexture.getSize().y);
}

void Graphical::draw() {
    renderTexture.clear(sf::Color::White);
    renderTexture.draw(sf::Sprite(backgroundTexture));
    renderTexture.draw(text);
    renderTexture.display();
}

void Graphical::setColor(sf::Color color){
    sf::Image image;
    image.create(CELL_LENGTH, CELL_WIDTH, color);
    backgroundTexture.loadFromImage(image);
} 