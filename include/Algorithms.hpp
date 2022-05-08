#pragma once

#include "ValuesAndTypes.hpp"

namespace Algorithms {
    double calculateAzimuth(const sf::Vector2f &from, const sf::Vector2f &to);
    double calculateAzimuth(const FieldCoord &from, const FieldCoord &to);

    sf::Vector2f calculateDistanceVector(const FieldCoord &from, const FieldCoord &to);
    sf::Vector2f calculateDistanceVector(const sf::Vector2f &from, const sf::Vector2f &to);
    double calculateManhattanDistance( const sf::Vector2f &from, const sf::Vector2f &to);
    double calculateEuclideanDistance( const sf::Vector2f &from, const sf::Vector2f &to);

    int fieldCoordToFlatIndex(const FieldCoord &fieldCoord);
    FieldCoord flatIndexToFieldCoord(const int index);

    FieldCoord vector2fToFieldCoord(const sf::Vector2f &floatFieldCoord);
    sf::Vector2f fieldCoordToVector2f(const FieldCoord &fieldCoord);
    sf::Vector2f fieldCoordToVector2fCentered(const FieldCoord &fieldCoord);
    
    bool inFieldBounds(sf::Vector2f floatCoord);

    int doubleRadiusToInt(double damageRadius);
    double intRadiusToDouble(int damageRadius);

    bool belongsToCircle(sf::Vector2f point, sf::Vector2f center, double radius);
    bool belongsToCircle(FieldCoord point, FieldCoord center, int radius);

    double radiansToDegrees( double radians);
}