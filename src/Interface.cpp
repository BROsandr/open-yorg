#include "Interface.hpp"
#include "Field/Field.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/View.hpp"
#include "ValuesAndTypes.hpp"
#include "Field/FieldCell.hpp"
#include "Game.hpp"

Interface::Interface(Field &field) : field{ field } {
	crystalsText.setFont(Game::font);
	crystalsText.setCharacterSize(60);
    crystalsText.setFillColor(sf::Color{0, 0, 77});
    crystalsText.setPosition({CELL_LENGTH * FIELD_LENGTH, 50.0});
}

void Interface::update(){
    crystalsText.setString(std::to_string( Game::crystals ));
}

void Interface::draw(){
    sf::View savedView { Game::window->getView()};
    Game::window->setView(Game::window->getDefaultView());
    Game::window->draw(crystalsText);
    Game::window->setView(savedView);
}

void Interface::selectCell(const FieldCoord &selection){
    if(selectedCell != NONE_FIELD_CELL)
        field.get(selectedCell).setOutlineColor(UNSELECTED);
    field.get(selection).setOutlineColor(SELECTED);
    selectedCell = selection;
}