#pragma once

#include "Building.hpp"
#include "Can/CanShoot.hpp"
#include "Can/CanStore.hpp"

class Enemies;
class Enemy;
class Bullets;
class DamageCircles;

class Cannon: public Building, public CanShoot, public CanStore{
public:
    Cannon(FieldCoord &fieldCoord, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles);
    void draw() override;
    void shootAim()override;
    void update()override;
    sf::Vector2f getCenter()const override;

private:
    Enemies &enemies;
    Enemy *aim = nullptr;
    Bullets &bullets;
    DamageCircles &damageCircles;
};