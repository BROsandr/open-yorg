#include "Interface/Interface.hpp"
#include "Field/Field.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/View.hpp"
#include "ValuesAndTypes.hpp"
#include "Field/FieldCell.hpp"
#include "Game.hpp"
#include <string>

Interface::Interface(Field &field) : field{ field } {
	crystalsText.setFont(Game::font);
	crystalsText.setCharacterSize(60);
    crystalsText.setFillColor(sf::Color{0, 0, 77});
}

void Interface::update(){
    crystalsText.setString(std::to_string(field.getCrystals()));
}

void Interface::draw(){
    crystalsText.setPosition({Game::window->getSize().x / 2.0f, 50.0f});
    sf::View savedView { Game::window->getView()};
    Game::window->setView(windowSizeView);
    Game::window->draw(crystalsText);
    layouts.update();
    Game::window->setView(savedView);
}

void Interface::selectCell(const FieldCoord &selection){
    if(selectedCell != NONE_FIELD_CELL)
        field.get(selectedCell).setOutlineColor(UNSELECTED);
    field.get(selection).setOutlineColor(SELECTED);
    selectedCell = selection;
}

std::string Interface::getButtonIfClicked(){
    return layouts.getButtonIfClicked();
}