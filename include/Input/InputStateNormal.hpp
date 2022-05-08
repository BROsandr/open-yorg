#pragma once

#include "Field/FieldCell.hpp"
#include "InputState.hpp"
#include "SFML/System/Vector2.hpp"
#include "ValuesAndTypes.hpp"

class Building;
class FieldCell;

class InputStateNormal:public InputState{
public:
	InputStateNormal(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_);
    InputState* processKeys(const sf::Event::KeyEvent &key) override;

private:

    bool isValidBuildingPosition(const FieldCoord &position);
    std::pair<FieldCell*, int> build(const sf::Keyboard::Key &key);
    void upgrade(Building &building);
    bool canAfford(Building &building);
    InputState* place(const sf::Keyboard::Key &key);
};