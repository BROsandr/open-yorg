#pragma once

#include "DamageCircle/DamageCircle.hpp"

class Field;

class EnemyDamageCircle : public DamageCircle {
public:
	EnemyDamageCircle(FieldCoord aim, double damage, int damageRadius, Field &field);
private:
	Field &field;

    void damageNearCells();
	bool belongsToCircle(sf::Vector2f point);
};