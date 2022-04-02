#pragma once

#include <vector>

#include "ValuesAndTypes.hpp"
#include "Road.hpp"
#include "PathSearchField.hpp"
#include "ValuesAndTypes.hpp"

class FieldCell;

class Field{
public:
    FieldCoord basePosition = NONE_FIELD_CELL;
    Road road;
    PathSearchField pathSearchField;

    Field();
    void tick();
    void update();
    void draw();
    void set(FieldCell *const fieldCell);
    FieldCell &get(const FieldCoord &fieldCoord);
    ~Field();

private:
    std::vector< std::vector<FieldCell*> > field;
};