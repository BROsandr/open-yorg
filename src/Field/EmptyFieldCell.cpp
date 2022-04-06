#include "Field/EmptyFieldCell.hpp"
#include "Game.hpp"

EmptyFieldCell::EmptyFieldCell(const FieldCoord &fieldCoord): FieldCell{fieldCoord}{
}

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
void EmptyFieldCell::draw(){
    FieldCell::draw();
    renderTexture.display();
    Game::window->draw(*this);
}

void EmptyFieldCell::update(){}