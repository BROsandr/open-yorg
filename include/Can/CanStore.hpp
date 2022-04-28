#pragma once

#include "Building/Building.hpp"
#include "ValuesAndTypes.hpp"

class CanStore: public Building{
public:
    CanStore(const FieldCoord &fieldCoord, int connectionRadius);
    double storage = 0;
    
    void draw() override;
    void update() override;
private:
    sf::Text storageText;
};