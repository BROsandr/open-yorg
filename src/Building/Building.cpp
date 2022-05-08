#include "Building/Building.hpp"
#include "SFML/Graphics/Color.hpp"

Building::Building(const FieldCoord &fieldCoord, int connectionRadius, int cost_): FieldCell{fieldCoord, connectionRadius}, cost{cost_}{
	fieldCellType = FieldCellType::building;
	setHp(12);
}

void Building::upgrade(){
	setColor(sf::Color(255, 102, 153, 200));
	setHp(getHp() * 2);
}

void Building::update() {
	if (getHp() <= 0)
		deleted = true;
}