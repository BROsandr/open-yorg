#pragma once

#include <SFML/Window/Event.hpp>

#include "ValuesAndTypes.hpp"

class Field;
class Interface;
class Enemies;
class PathSearchField;
class Bullets;
class DamageCircles;
class Road;
class ResourceBalls;

class Input{
public:
    Input(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles, ResourceBalls &resourceBalls, Road &road);
    void process(const sf::Event &event);

private:
    Field &field;
    Interface &interface;
    Enemies &enemies;
    PathSearchField &pathSearchField;
    Bullets &bullets;
    DamageCircles &damageCircles;
    ResourceBalls &resourceBalls;
    Road &road;

    bool isValidBuildingPosition(const FieldCoord &position);
    void processMouseWheelScroll(const sf::Event::MouseWheelScrollEvent &mouseWheelScroll);
    void processMouseClick(const sf::Event::MouseButtonEvent  &mouseButton);
    void processKeys(const sf::Event::KeyEvent &key);
    void processMouseLeftClick(const sf::Vector2i &clickPosition);
    void build(const sf::Keyboard::Key &key);
};