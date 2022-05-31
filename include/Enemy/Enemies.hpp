#pragma once

#include <list>

#include "DamageCircle/DamageCircles.hpp"
#include "ValuesAndTypes.hpp"

class Enemy;
class Field;
class PathSearchField;
class Bullets;
class DamageCircles;

class Enemies{
public:
    Enemies(Field &field);
    Enemy *append(Enemy *enemy);
    Enemy &findNearest(FieldCoord fieldCoord);
    std::vector<Enemy *> findAllInCircle(sf::Vector2f circleCenter, double searchRadius);
    void spawnInRandomPos(PathSearchField &pathSearchField, Bullets &bullets, DamageCircles &damageCircles);

private:
    std::list<Enemy*> enemies;
    Field &field;

    void update();
    void draw();

    friend class GameElements;
};