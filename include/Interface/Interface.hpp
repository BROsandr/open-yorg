#pragma once

#include "Interface/Layout.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/View.hpp"
#include "ValuesAndTypes.hpp"
#include "Interface/Layouts.hpp"
#include <list>

class Field;

class Interface{
public:
    FieldCoord selectedCell;

    Interface(Field &field);
    void update();
    void draw();
    void selectCell(const FieldCoord &selection);
    sf::View windowSizeView;

private:
    Field &field;
    sf::Text crystalsText;
    Layouts layouts;
};