#include "Bullet/EnemyBullet.hpp"
#include "Algorithms.hpp"
#include "DamageCircle/EnemyDamageCircle.hpp"
#include "DamageCircle/DamageCircles.hpp"

EnemyBullet::EnemyBullet(sf::Vector2f spawnPosition, FieldCoord aim, double damage, Field &field, int damageRadius, DamageCircles &damgeCircles_) : Bullet { spawnPosition, aim, damage, damageRadius }, field{ field }, damageCircles{ damgeCircles_ } {
	speed = 0.01 * CELL_LENGTH;
}

void EnemyBullet::move_(){
    Bullet::move_();
    if (Algorithms::calculateEuclideanDistance(getCenter(), getAimCoord<sf::Vector2f>()) < speed) {
        damageCircles.append(new EnemyDamageCircle(getAimCoord<FieldCoord>(), damage, getDamageRadius<int>(), field));
        deleted = true;
    }
}

