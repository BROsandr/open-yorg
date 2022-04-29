#include "Building/Mine.hpp"
#include "Game.hpp"
#include "Resource/ResourceBalls.hpp"
#include "Resource/ResourceBall.hpp"

Mine::Mine(Field &field, const FieldCoord &fieldCoord, double miningRate_, ResourceBalls &resourceBalls_, Road& road_) : resourceBalls{ resourceBalls_ },Building{ fieldCoord, 2 }, field{field}, miningRate{ miningRate_ }, road{ road_ } {
    buildingType = BuildingType::mine;
}
void Mine::update(){
    if(isTimeToMine() && road.mineHasResource(getCoord(), compatibleResource))
        mine();
}

void Mine::draw() {
    Building::draw();
    renderTexture.display();
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