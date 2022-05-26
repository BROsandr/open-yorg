#include "Resource/ResourceBall.hpp"
#include "Can/CanStore.hpp"
#include "Graphical.hpp"
#include "Resource/ResourceBalls.hpp"
#include "Algorithms.hpp"
#include "Field/Road.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"
#include "ValuesAndTypes.hpp"
#include "Game.hpp"
#include "Field/FieldCell.hpp"
#include "Building/Building.hpp"

ResourceBall::ResourceBall(Field &field_, Road &road, const FieldCoord &source, ResourceType type_) : type{type_}, road{road}, source { source }, destination{ source }, destinationNode{ source }, field{field_}{
    findDestination();
    speed = 0.01 * CELL_LENGTH ;
    setRadius(CELL_LENGTH / 4.);
    setPosition(Algorithms::fieldCoordToVector2fCentered(source) - sf::Vector2f{ getRadius(), getRadius() });
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(CELL_OUTLINE_THICKNESS);
    setTexture(&renderTexture.getTexture());
    nextMoveFieldCoord = Algorithms::vector2fToFieldCoord(getCenter());
    if(type == ResourceType::crystal)
        setColor(sf::Color::Magenta);
    else if(type == ResourceType::iron)
        setColor(sf::Color::Yellow);
    if(!road.mineHasResource(source, type))
        fade();
}

ResourceBall::~ResourceBall(){
    delete fadingClock;
}

void ResourceBall::fade(){
    setRandomMovementAzimuth();
    fading = true;
    fadingClock = new sf::Clock;
}

void ResourceBall::update(){
    double distance = Algorithms::calculateEuclideanDistance(getCenter(), Algorithms::fieldCoordToVector2fCentered(nextMoveFieldCoord) );
    if (distance < speed && !fading) 
        findNextNode();
    double fadingTime = 1.5;
    if(fading && fadingTime < fadingClock->getElapsedTime().asSeconds())
        deleted = true;
	else
        move_();
}

void ResourceBall::draw(){
    Graphical::draw();
    Game::window->draw(*this);
}

void ResourceBall::findDestinationNode(){
}

void ResourceBall::findDestination(){
}

void ResourceBall::increaseResource(){
    static_cast<CanStore&>(field.get(nextMoveFieldCoord)).storage++;
}

void ResourceBall::erase(){
}

void ResourceBall::updatePosition(){
}

void ResourceBall::move_(){
    sf::Vector2f step = getMovementVector();
    move(step);
}

bool ResourceBall::reachedDestination(FieldCoord &fieldCoord){
    return fieldCoord == Algorithms::vector2fToFieldCoord(getCenter());
}

sf::Vector2f ResourceBall::getCenter()const{
    return getPosition() + sf::Vector2f{getRadius(), getRadius()};
}

void ResourceBall::findNextNode(){
    FieldCoord selfCoord = Algorithms::vector2fToFieldCoord(getCenter());
    bool reached = false;
    std::tie(nextMoveFieldCoord, reached) = road.generatePath(selfCoord, type);
    if(!reached)
        fade();
    else if(reachedDestination(nextMoveFieldCoord)){
        increaseResource();
        deleted = true;
    }
    else{
        setMovementAzimuth(getCenter(), Algorithms::fieldCoordToVector2fCentered(nextMoveFieldCoord));
    }
}