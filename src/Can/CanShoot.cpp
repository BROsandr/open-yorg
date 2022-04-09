#include <SFML/System/Time.hpp>

#include "Can/CanShoot.hpp"

CanShoot::CanShoot(FieldCoord aim, double damage, int damageRadius) : CanDamage{ aim, damage, damageRadius } {};
CanShoot::CanShoot(sf::Vector2f aim, double damage, double damageRadius) : CanDamage{ aim, damage, damageRadius } {};

void CanShoot::shootAim() {
	fireRateClock.restart();
}

void CanShoot::findAim() {

}
bool CanShoot::isTimeToShoot() {
	if (fireRate < fireRateClock.getElapsedTime().asSeconds()) 
		return true;
	else
		return false;
}