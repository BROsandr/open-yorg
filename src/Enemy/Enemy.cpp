#include <SFML/Graphics/Sprite.hpp>

#include "Enemy/Enemy.hpp"
#include "Algorithms.hpp"
#include "Game.hpp"
#include "Bullet/EnemyBullet.hpp"
#include "Field/FieldCell.hpp"
#include "Building/Building.hpp"

Enemy::Enemy(const FieldCoord &spawnPosition, PathSearchField &pathSearchField, Bullets &bullets, double damage, Field &field, int damageRadius, DamageCircles &damageCircles_) : CanShoot{ NONE_FIELD_CELL, damage, damageRadius }, field{ field }, pathSearchField{ pathSearchField }, bullets { bullets }, damageCircles{ damageCircles_ } {
    setPosition(Algorithms::fieldCoordToVector2f(spawnPosition));
    setRadius(CELL_LENGTH / static_cast<double>(2));
    setOutlineColor(UNSELECTED);
    setOutlineThickness(CELL_OUTLINE_THICKNESS);
    setTexture(&renderTexture.getTexture());
    nextMoveFieldCoord = Algorithms::vector2fToFieldCoord(getCenter());

    text.setString("E");
}

void Enemy::draw(){
    Graphical::draw();
    Game::window->draw(*this);
}

void Enemy::move_() {
    sf::Vector2f step = getMovementVector();
    move(step);
}

void Enemy::findNextNode(){
        FieldCoord selfCoord = Algorithms::vector2fToFieldCoord(getCenter());
        bool reached = false;
        std::tie(nextMoveFieldCoord, reached) = pathSearchField.generatePath(selfCoord);
        if(field.isFutureCell(nextMoveFieldCoord))
            return;
        if(!reached)
            nextMoveFieldCoord = selfCoord;
        setMovementAzimuth(getCenter(), Algorithms::fieldCoordToVector2fCentered(nextMoveFieldCoord));
        if (field.get(nextMoveFieldCoord).fieldCellType == FieldCell::FieldCellType::building) {
            attacking = true;
            setAimCoord(nextMoveFieldCoord);
        }
}
    

void Enemy::update(){
	if (getHp() <= 0){
		deleted = true;
        return;
    }
    double distance = Algorithms::calculateEuclideanDistance(getCenter(), Algorithms::fieldCoordToVector2fCentered(nextMoveFieldCoord) );
    if (distance < speed )
        findNextNode();
    if (!attacking)
        move_();
    else {
        if (static_cast<Building&>(field.get(getAimCoord<FieldCoord>())).getHp() > 0){
            if(isTimeToAttack())
                attack();
        }
        else
            attacking = false;
    }
}

void Enemy::shootAim() {
    CanShoot::shootAim();
    bullets.append(new EnemyBullet{ getCenter(), getAimCoord<FieldCoord>(), damage, field, getDamageRadius<int>(), damageCircles });
}

sf::Vector2f Enemy::getCenter()const{
    return getPosition() + sf::Vector2f{getRadius(), getRadius()};
}