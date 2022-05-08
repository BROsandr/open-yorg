#include "Input/InputStateFutureRoad.hpp"
#include "Algorithms.hpp"
#include "Field/Road.hpp"
#include "Input/InputState.hpp"
#include "Input/Input.hpp"
#include "Input/InputStateNormal.hpp"
#include "Field/Field.hpp"
#include "Game.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Mouse.hpp"
#include "ValuesAndTypes.hpp"

InputStateFutureRoad::InputStateFutureRoad(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_, int buildingCost, FieldCell *fieldCell): fieldCell(fieldCell), InputState(field, interface, pathSearchField, enemies, bullets, damageCircles_, resourceBalls_, road_), buildingCost(buildingCost){}

InputState* InputStateFutureRoad::processKeys(const sf::Event::KeyEvent &key){
    switch(key.code){
    case sf::Keyboard::Key::Enter:
        road.showRealRoad(false);
        field.decreaseCrystals(buildingCost);
        break;
    case sf::Keyboard::Key::Escape:
        road.showRealRoad(true);
        break;
	}
    return new InputStateNormal{field, interface, pathSearchField, enemies, bullets, damageCircles, resourceBalls, road};
}

void InputStateFutureRoad::processMouseMove(const sf::Event::MouseMoveEvent &mouseMove){
    sf::Vector2f mousePos { Game::window->mapPixelToCoords(sf::Mouse::getPosition(*Game::window))};
    FieldCoord fieldCoord{ Algorithms::vector2fToFieldCoord(mousePos)};
    if(fieldCell->getCoord() != fieldCoord && Algorithms::inFieldBounds(mousePos))
        field.relocate(*fieldCell, fieldCoord);
}