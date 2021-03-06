#include "Field/FieldCell.hpp"
#include "Algorithms.hpp"

FieldCell::FieldCell(const FieldCoord &fieldCoord, int connectionRadius_): connectionRadius{connectionRadius_}{
    setCoord(fieldCoord);
    setSize({CELL_LENGTH, CELL_WIDTH});
    setOutlineColor(UNSELECTED);
    setOutlineThickness(CELL_OUTLINE_THICKNESS);

    setTexture(&renderTexture.getTexture());
}

void FieldCell::setCoord(const FieldCoord &fieldCoord){
    setPosition(Algorithms::fieldCoordToVector2f(fieldCoord));
    coord = fieldCoord;
}

FieldCoord FieldCell::getCoord(){
    return coord;
}

void FieldCell::draw(){
    Graphical::draw();
    // image.create(Settings::Field::cellLength, Settings::Field::cellWidth, Color::White);
    // text.loadFromImage(image);
}

sf::Vector2f FieldCell::getCenter()const{
    return getPosition() + sf::Vector2f{ getSize().x / 2, getSize().y / 2 };
}