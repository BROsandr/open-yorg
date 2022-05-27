#pragma once

#include "InputState.hpp"
#include <SFML/Window/Keyboard.hpp>

class FieldCell;

class InputStateFutureRoad: public InputState{
public:
	InputStateFutureRoad(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_, int buildingCost, FieldCell *fieldCell);
    InputState* processKeys(const sf::Keyboard::Key &key) override;
    void processMouseMove() override;
private:
	int buildingCost = 0;
	FieldCell *fieldCell = nullptr;
};