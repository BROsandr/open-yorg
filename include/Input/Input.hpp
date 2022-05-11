#pragma once

#include <SFML/Window/Event.hpp>

#include "InputState.hpp"
#include "ValuesAndTypes.hpp"

class Field;
class Interface;
class Enemies;
class PathSearchField;
class Bullets;
class DamageCircles;
class Road;
class ResourceBalls;
class InputState;

class Input{
public:
    Input(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles, ResourceBalls &resourceBalls, Road &road);
    void process(const sf::Event &event);

private:
	// state pattern
    InputState *state = nullptr;
    Interface &interface;
    const sf::Vector2f left {-1, 0};
    const sf::Vector2f right{1, 0};
    const sf::Vector2f up{0, -1};
    const sf::Vector2f down{0, 1};
    sf::Vector2i middleButtonPrevPos{NONE, NONE};

    void processMouseWheelScroll(const sf::Event::MouseWheelScrollEvent &mouseWheelScroll);
    void zoomView(const double delta);
    void processViewMove(const sf::Keyboard::Key &key);
    void processKeys(const sf::Event::KeyEvent &key);
    void processMouseClick(const sf::Event::MouseButtonEvent  &mouseButton);
    void processMouseLeftClick(const sf::Vector2i &clickPosition);
    void processMiddleButtonPressed();
    void moveView(const sf::Vector2f delta);

    friend class InputStateNormal;
    friend class InputStateFutureRoad;
};