#pragma once

#include <SFML/Window/Event.hpp>

#include "InputState.hpp"
#include "InputStateFutureRoad.hpp"
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

    friend class InputStateNormal;
    friend class InputStateFutureRoad;
};