#pragma once

#include "SFML/Graphics/Text.hpp"
#include "ValuesAndTypes.hpp"

class Field;

class Interface{
public:
    FieldCoord selectedCell;

    Interface(Field &field);
    void update();
    void draw();
    void selectCell(const FieldCoord &selection);

private:
    Field &field;
    sf::Text crystalsText;
};