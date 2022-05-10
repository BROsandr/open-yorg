#pragma once

#include <list>

#include "ValuesAndTypes.hpp"

class Enemy;

class Enemies{
public:
    Enemies();
    Enemy *append(Enemy *enemy);
    Enemy &findNearest(FieldCoord fieldCoord);
    std::vector<Enemy *> findAllInCircle(sf::Vector2f circleCenter, double searchRadius);

private:
    std::list<Enemy*> enemies;

    void update();
    void draw();

    friend class GameElements;
};