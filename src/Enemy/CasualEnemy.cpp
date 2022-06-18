#include "Enemy/CasualEnemy.hpp"
#include "Enemy/Enemies.hpp"

CasualEnemy::CasualEnemy(const FieldCoord &spawnPosition, Enemies &enemies, PathSearchField &pathSearchField, Bullets &bullets, Field &field, DamageCircles &damageCircles) : Enemy{ spawnPosition, pathSearchField, bullets, 4, field, 1, damageCircles } {
	fireRate = 1;
	speed = 0.01 * CELL_LENGTH;
	setHp(12);
}
