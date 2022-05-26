#include "Building/Mine.hpp"
#include "Building/Building.hpp"
#include "Game.hpp"
#include "Resource/ResourceBalls.hpp"
#include "Resource/ResourceBall.hpp"

Mine::Mine(Field &field, const FieldCoord &fieldCoord, double miningRate_, ResourceBalls &resourceBalls_, Road& road_) : Building{ fieldCoord, 2, 0 },miningRate{ miningRate_ }, resourceBalls{ resourceBalls_ }, road{ road_ }, field{field} {
    buildingType = BuildingType::mine;
}
void Mine::update(){
    Building::update();
    if(isTimeToMine() && road.mineHasResource(getCoord(), compatibleResource))
        mine();
}

void Mine::draw() {
    Building::draw();
    Game::window->draw(*this);
}

bool Mine::isTimeToMine(){
	if (miningRate < miningRateClock.getElapsedTime().asSeconds()) 
		return true;
	else
		return false;
}
void Mine::mine(){
    miningRateClock.restart();
	resourceBalls.append(new ResourceBall{field, road, getCoord(), compatibleResource});
}