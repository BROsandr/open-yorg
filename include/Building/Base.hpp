#pragma once

#include "Building/Building.hpp"
#include "Can/CanStore.hpp"

class Field;

class Base: public CanStore{
public:
    Base(Field &field, const FieldCoord &fieldCoord);
    ~Base() override;

    void draw()override;
    void update() override;
    
private:
    Field &field;
};