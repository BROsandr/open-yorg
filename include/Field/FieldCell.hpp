#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ValuesAndTypes.hpp"
#include "Graphical.hpp"

class FieldCell: public sf::RectangleShape, public Graphical{
public:
    bool isEmpty = false;

    FieldCell(const FieldCoord &fieldCoord);
    void setCoord(const FieldCoord &fieldCoord);
    FieldCoord getCoord();
    void draw()override;

protected:
    FieldCoord coord = NONE_FIELD_CELL;

private:
};