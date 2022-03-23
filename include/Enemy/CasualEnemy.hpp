#pragma once

#include "Enemy/Enemy.hpp"

class Enemies;

class CasualEnemy: public Enemy{
public:
	CasualEnemy(const FieldCoord &spawnPosition, Enemies &enemies, PathSearchField &pathSearchField);
};