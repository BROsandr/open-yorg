#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>

#include "Can/CanMove.hpp"
#include "Graphical.hpp"
#include "SFML/System/Vector2.hpp"
#include "ValuesAndTypes.hpp"

class ResourceBalls;
class Road;
class Field;

class ResourceBall: public CanMove, public Graphical, public sf::CircleShape{
public:
    ResourceType type = ResourceType::none;

    ResourceBall(Field &field, Road &road, const FieldCoord &source, ResourceType type);
    virtual ~ResourceBall();
    sf::Vector2f getCenter()const override;
    void draw()override;
    void update();
protected:
    virtual void findDestinationNode();
    virtual void findDestination();
    void increaseResource();
    void erase();
    void updatePosition();

private:
    Road &road;
    FieldCoord source = NONE_FIELD_CELL;
    FieldCoord sourceNode = NONE_FIELD_CELL;
    FieldCoord destination = NONE_FIELD_CELL;
    FieldCoord nextNode = NONE_FIELD_CELL;
    FieldCoord destinationNode = NONE_FIELD_CELL;
    FieldCoord currentNode = NONE_FIELD_CELL;
    Field &field;
    bool fading = false;
    sf::Clock *fadingClock = nullptr;

    void move_()override;
    void fade();
    bool reachedDestination(FieldCoord &fieldCoord);
    void findNextNode();
};