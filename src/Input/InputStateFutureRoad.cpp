#include "Input/InputStateFutureRoad.hpp"
#include "Field/Road.hpp"
#include "Input/InputState.hpp"
#include "Input/Input.hpp"
#include "Input/InputStateNormal.hpp"
#include "Field/Field.hpp"

InputStateFutureRoad::InputStateFutureRoad(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_, int buildingCost): InputState(field, interface, pathSearchField, enemies, bullets, damageCircles_, resourceBalls_, road_), buildingCost(buildingCost){}

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