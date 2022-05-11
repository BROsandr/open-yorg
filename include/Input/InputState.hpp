#pragma once
#include "SFML/Window/Event.hpp"
#include "ValuesAndTypes.hpp"

class Input;
class Field;
class Interface;
class Enemies;
class PathSearchField;
class Bullets;
class DamageCircles;
class Road;
class ResourceBalls;


class InputState{
public:
	InputState(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_);
    virtual ~InputState() = default;
    virtual InputState* processKeys(const sf::Event::KeyEvent &key) = 0;
    virtual void processMouseMove() = 0;
protected:
    Field &field;
    Interface &interface;
    Enemies &enemies;
    PathSearchField &pathSearchField;
    Bullets &bullets;
    DamageCircles &damageCircles;
    ResourceBalls &resourceBalls;
    Road &road;
};