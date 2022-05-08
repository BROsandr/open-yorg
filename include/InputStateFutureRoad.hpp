#pragma once

#include "InputState.hpp"

class InputStateFutureRoad: public InputState{
public:
	InputStateFutureRoad(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_, int buildingCost);
	InputState* process(const sf::Event &event) override;
private:
    InputState* processKeys(const sf::Event::KeyEvent &key) override;
	int buildingCost = 0;
};