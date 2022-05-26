#include "Field/EmptyFieldCell.hpp"
#include "Game.hpp"
#include "ValuesAndTypes.hpp"

EmptyFieldCell::EmptyFieldCell(const FieldCoord &fieldCoord): FieldCell{fieldCoord, NONE}{
    fieldCellType = FieldCellType::empty;
}

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
void EmptyFieldCell::draw(){
    FieldCell::draw();
    Game::window->draw(*this);
}

void EmptyFieldCell::update(){}