#include "Bullet/Bullet.hpp"
#include "Algorithms.hpp"
#include "Game.hpp"

// Bullet::Bullet(aim, damage): aim{aim}, damage{damage}{
//     Game::gameElements.ammunitions.add(*this)
//     movementAzimuth = Algorithms::calculateAzimuth(getCenter(), aim)
// }

// update(){
//     if(!aim.contains(getCenter())
//         move(movementAzimuth * speed, movementAzimuth * speed
//     else{
//         damage()
//         erase()
//     }
// }

// damage(){
//     foreach i in creatures
//         if(distance(i.getCenter(), getCenter()) < radius){
//             i.hp -= damage;
//         }
// }

// erase(){
//     erased = true;
// }

Bullet::Bullet(sf::Vector2f spawnPosition, FieldCoord aim) : CanDamage{ aim } {
    setRadius(CELL_LENGTH / 4.);
    setPosition(spawnPosition - sf::Vector2f{getRadius(), getRadius()});
    setMovementAzimuth(this->getCenter(), Algorithms::mapFieldCoordToVector2fCentered(aim) );
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(CELL_OUTLINE_THICKNESS);
    setTexture(&renderTexture.getTexture());

    renderTexture.draw(text);
}

void Bullet::draw(){
    Graphical::draw();
    renderTexture.display();
    Game::window->draw(*this);
}

void Bullet::move_() {
    sf::Vector2f distance = Algorithms::calculateDistanceVector(getCenter(), Algorithms::mapFieldCoordToVector2fCentered(aim));
    if (abs(distance.x) < speed && abs(distance.y) < speed) {
        deleted = true;
    }
    sf::Vector2f step = getMovementVector();
    move(step);
}

void Bullet::update() {
    move_();
}

sf::Vector2f Bullet::getCenter() {
    return getPosition() + sf::Vector2f{getRadius(), getRadius()};
}