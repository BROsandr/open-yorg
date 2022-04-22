#include "Resource/ResourceBall.hpp"
#include "Resource/ResourceBalls.hpp"
#include "Algorithms.hpp"
#include "Field/Road.hpp"

ResourceBall::ResourceBall(Road &road, const FieldCoord &source) : road{road}, source { source }, destination{ source }, destinationNode{ source }{
    // if(const FieldCell &fieldCell = Game::gameElements.field.get(source); fieldCell.type == FieldCell::Types::buidling)
    //     if(Building building = static_cast<Building&>(fieldCell); building.type == Building::Types::Mine)
    //         if(Mine mine = static_cast<Mine&>(fieldCell); mine.type == Mine::Types::crystal)
    //             type = Resource::Types::crystal;
}

void ResourceBall::create(ResourceBalls &resourceBalls, const size_t amount){
    findDestination();
    resourceBalls.append(amount, *this);
}

void ResourceBall::update(){
    // if(destinationNode or sourceNode have been deleted){
    //     fade()
    //     erase()
    // } 
    // if(getCenter() == destinationNode && destinationNode == destination){
    //     increaseResource()
    //     erase()
    // }
    // else if(getCenter() == destinationNode && destinationNode == destination && destinationNode == sourceNode){
    //     fade()
    //     erase()
    // }
    // if(getCenter() == destinationNode && destinationNode != destination){
    //     findDestinationNode()
    // }
    // updatePosition()
}

void ResourceBall::findDestinationNode(){
    // destinationNode = road.findPath(currentNode, destination);
    // movementAzimuth = Algorithms::calculateAzimuth(currentNode, destinationNode);
}

void ResourceBall::findDestination(){
    // if(type == Resource::Types::crystal){
    //     destination = Game::gameElements.field.basePosition;
    // }
    // ...
}

void ResourceBall::increaseResource(){
    // if(type == Resource::Types::crystal){
    //     static_cast<Base&>(Game::gameElements.field.get( (Game::gameElements.field.basePosition) ) ).storage++;
    // }
    // ...
}

void ResourceBall::erase(){
    isSupposedToBeDeleted = true;
}

void ResourceBall::updatePosition(){
    // moveAtAzimuth(movementAzimuth);
}