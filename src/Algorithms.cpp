#include <SFML/System/Vector2.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Algorithms.hpp"
#include "ValuesAndTypes.hpp"

double Algorithms::calculateAzimuth(const sf::Vector2f &from, const sf::Vector2f &to) {
    return atan2(to.y - from.y, to.x - from.x);
}

double Algorithms::calculateAzimuth(const FieldCoord &from_, const FieldCoord &to_) {
    sf::Vector2f from = fieldCoordToVector2fCentered(from_);
    sf::Vector2f to = fieldCoordToVector2fCentered(to_);
    return calculateAzimuth(from, to);
}

sf::Vector2f Algorithms::calculateDistanceVector(const sf::Vector2f &from, const sf::Vector2f &to) {
    return { static_cast<float>(to.x - from.x), static_cast<float>(to.y - from.y) };
}

FieldCoord Algorithms::vector2fToFieldCoord(const sf::Vector2f &floatFieldCoord){
    int x = floatFieldCoord.x / CELL_LENGTH;
    int y = floatFieldCoord.y / CELL_WIDTH;

    return FieldCoord(x, y);
}

sf::Vector2f Algorithms::fieldCoordToVector2f(const FieldCoord &fieldCoord) {
    int x = fieldCoord.x * CELL_LENGTH;
    int y = fieldCoord.y * CELL_WIDTH;

    return sf::Vector2f(x, y);
}

sf::Vector2f Algorithms::fieldCoordToVector2fCentered(const FieldCoord &fieldCoord) {
    sf::Vector2f vector = fieldCoordToVector2f(fieldCoord);

    return { vector.x + CELL_LENGTH / 2, vector.y + CELL_WIDTH / 2 };
}

int Algorithms::fieldCoordToFlatIndex(const FieldCoord &fieldCoord) {
    return fieldCoord.x + fieldCoord.y * FIELD_LENGTH;
}

FieldCoord Algorithms::flatIndexToFieldCoord(const int index) {
    return FieldCoord(index % FIELD_LENGTH, index / FIELD_LENGTH);
}
// Resource Algorithms::enumToClass(const Resource::Types type);

int Algorithms::doubleRadiusToInt(double damageRadius) {
    return 1 + (damageRadius - (CELL_LENGTH / 2) ) / CELL_LENGTH;
}

double Algorithms::intRadiusToDouble(int damageRadius) {
    return (damageRadius - 1) * CELL_LENGTH + CELL_LENGTH / 2;
}

bool Algorithms::belongsToCircle(sf::Vector2f point, sf::Vector2f center, double radius) {
    return calculateEuclideanDistance(point, center) < radius;
}

bool Algorithms::belongsToCircle(FieldCoord point, FieldCoord center, int radius) {
    return belongsToCircle(fieldCoordToVector2fCentered(point), fieldCoordToVector2fCentered(center), intRadiusToDouble(radius));
}

double Algorithms::calculateManhattanDistance( const sf::Vector2f &from, const sf::Vector2f &to){
    return abs(to.x - from.x);
}

double Algorithms::calculateEuclideanDistance( const sf::Vector2f &from, const sf::Vector2f &to){
    return sqrt((to.x - from.x) * (to.x - from.x) + (to.y - from.y) * (to.y - from.y));
}

double Algorithms::radiansToDegrees( double radians){
    return radians * (180.0/M_PI);
}

bool Algorithms::inFieldBounds(sf::Vector2f floatCoord){
    FieldCoord fieldCell = Algorithms::vector2fToFieldCoord(floatCoord);
    return  (fieldCell.x < FIELD_LENGTH && floatCoord.x >= 0) && (fieldCell.y < FIELD_WIDTH && floatCoord.y >= 0);
}

sf::Vector2f Algorithms::getFieldSize(){
    return {FIELD_LENGTH * CELL_LENGTH, FIELD_WIDTH * CELL_WIDTH};
}