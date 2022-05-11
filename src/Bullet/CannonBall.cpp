#include "Bullet/CannonBall.hpp"
#include "Algorithms.hpp"
#include "DamageCircle/BuildingDamageCircle.hpp"
#include "DamageCircle/DamageCircles.hpp"
#include "SFML/System/Vector2.hpp"

CannonBall::CannonBall(sf::Vector2f spawnPosition, sf::Vector2f aim_, double damage, double damageRadius, DamageCircles &damgeCircles_, Enemies &enemies) : Bullet{ spawnPosition, aim_, damage, damageRadius }, damageCircles{ damgeCircles_ }, enemies{ enemies } {
    speed = 0.01 * CELL_LENGTH;
}

void CannonBall::move_() {
    Bullet::move_();
    if (Algorithms::calculateEuclideanDistance(getCenter(), getAimCoord<sf::Vector2f>()) < speed) {
        damageCircles.append(new BuildingDamageCircle(getAimCoord<sf::Vector2f>(), damage, getDamageRadius<double>(), enemies));
        deleted = true;
    }
}

