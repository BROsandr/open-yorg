#pragma once

#include "ValuesAndTypes.hpp"

class CanDamage{
public:
    CanDamage(FieldCoord aim, double damage);

    double damageRadius = NONE;
    double damage = NONE;
    FieldCoord aim = NONE_FIELD_CELL;

    virtual void update();
};