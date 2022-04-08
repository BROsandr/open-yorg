#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <lemon/dijkstra.h>
#include <lemon/list_graph.h>

#include "Can/CanMove.hpp"
#include "Can/CanHaveHp.hpp"
#include "Can/CanShoot.hpp"
#include "Graphical.hpp"

class PathSearchField;
class Bullets;
class Building;
class Field;
class DamageCircles;

class Enemy: public CanMove, public CanHaveHp, public CanShoot, public sf::CircleShape, public Graphical {
public:
    Enemy(const FieldCoord &spawnPosition, PathSearchField &pathSearchField, Bullets &bullets, double damage, Field &field, double damageRadius, DamageCircles &damageCircles);
    virtual ~Enemy() = default;
    void attack();
    void draw() override;
    virtual void update();

protected:
    FieldCoord nextMoveFieldCoord;
    sf::Vector2f getCenter() override;
private:
    Field &field;
    PathSearchField &pathSearchField;
    Bullets &bullets;
    bool attacking = false;
    DamageCircles &damageCircles;
    
    void move_();
    void shootAim()override;
};