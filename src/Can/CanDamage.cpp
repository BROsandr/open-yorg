#include "Can/CanDamage.hpp"
#include "Algorithms.hpp"

CanDamage::CanDamage(sf::Vector2f aim_, double damage, double damageRadius_) : damage{ damage }, damageRadius{damageRadius_}, aim{aim_}{
}
CanDamage::CanDamage(FieldCoord aim_, double damage, int damageRadius_) : damage{ damage }, damageRadius{Algorithms::intRadiusToDouble(damageRadius_)}, aim{Algorithms::fieldCoordToVector2fCentered(aim_)} {
}

template<>
int CanDamage::getDamageRadius() {
	return Algorithms::doubleRadiusToInt(damageRadius);
}

template<>
double CanDamage::getDamageRadius() {
	return damageRadius;
}

template<>
FieldCoord CanDamage::getAimCoord() {
	return Algorithms::vector2fToFieldCoord(aim);
}
template<>
sf::Vector2f CanDamage::getAimCoord() {
	return aim;
}

template<>
void CanDamage::setDamageRadius(int damageRadius_) {
	damageRadius = Algorithms::intRadiusToDouble(damageRadius_);
}
template<>
void CanDamage::setDamageRadius(double damageRadius_) {
	damageRadius = damageRadius_;
}

template<>
void CanDamage::setAimCoord(FieldCoord aim_) {
	aim = Algorithms::fieldCoordToVector2fCentered(aim_);
}
template<>
void CanDamage::setAimCoord(sf::Vector2f aim_) {
	aim = aim_;
}