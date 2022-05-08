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
	InputState* process(const sf::Event &event) override;

private:
    const sf::Vector2f left {-1, 0};
    const sf::Vector2f right{1, 0};
    const sf::Vector2f up{0, -1};
    const sf::Vector2f down{0, 1};
    sf::Vector2i middleButtonPrevPos{NONE, NONE};
    double zoomFactor = NONE;

    bool isValidBuildingPosition(const FieldCoord &position);
    void processMouseWheelScroll(const sf::Event::MouseWheelScrollEvent &mouseWheelScroll);
    void processMouseClick(const sf::Event::MouseButtonEvent  &mouseButton);
    InputState* processKeys(const sf::Event::KeyEvent &key) override;
    void processMouseLeftClick(const sf::Vector2i &clickPosition);
    std::pair<FieldCell*, int> build(const sf::Keyboard::Key &key);
    void upgrade(Building &building);
    bool canAfford(Building &building);
    InputState* place(const sf::Keyboard::Key &key);
    void moveView(const sf::Vector2f delta);
    void processMiddleButtonPressed();
    void zoomView(const double delta);
};