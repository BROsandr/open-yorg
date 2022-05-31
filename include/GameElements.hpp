#pragma once

#include "Field/Field.hpp"
#include "Enemy/Enemies.hpp"
#include "Resource/ResourceBalls.hpp"
#include "Bullet/Bullets.hpp"
#include "DamageCircle/DamageCircles.hpp"

class GameElements{
public:
    GameElements();
    Field field;
    Enemies enemies;
    ResourceBalls resourceBalls;
    Bullets bullets;
    DamageCircles damageCircles;

    void tick();
};