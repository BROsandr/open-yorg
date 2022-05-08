#pragma once

#include "Field/FieldCell.hpp"
#include "InputState.hpp"

class Building;
class FieldCell;

class InputStateNormal:public InputState{
public:
	InputStateNormal(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_);
	InputState* process(const sf::Event &event) override;

private:
    bool isValidBuildingPosition(const FieldCoord &position);
    void processMouseWheelScroll(const sf::Event::MouseWheelScrollEvent &mouseWheelScroll);
    void processMouseClick(const sf::Event::MouseButtonEvent  &mouseButton);
    InputState* processKeys(const sf::Event::KeyEvent &key) override;
    void processMouseLeftClick(const sf::Vector2i &clickPosition);
    std::pair<FieldCell*, int> build(const sf::Keyboard::Key &key);
    void upgrade(Building &building);
    bool canAfford(Building &building);
    InputState* place(const sf::Keyboard::Key &key);
};