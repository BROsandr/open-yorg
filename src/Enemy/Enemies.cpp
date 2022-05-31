#include "Enemy/Enemies.hpp"
#include "Enemy/Enemy.hpp"
#include "Algorithms.hpp"
#include "SFML/System/Vector2.hpp"
#include "ValuesAndTypes.hpp"
#include <random>
#include <Field/Field.hpp>
#include <Enemy/CasualEnemy.hpp>

Enemies::Enemies(Field &field) : field{field} {
}

Enemy *Enemies::append(Enemy *enemy) {
    enemies.push_front(enemy);
    return enemy;
}

void Enemies::update() {
    for (auto &enemy : enemies) {
        if(enemy->deleted){
            delete enemy;
            enemy = nullptr;
            continue;
        }
        enemy->update();
    }
    enemies.remove(nullptr);
}

void Enemies::draw() {
    for (auto &el : enemies)
        el->draw();
}

Enemy &Enemies::findNearest(FieldCoord fieldCoord) {

    return **std::min_element(enemies.begin(), enemies.end(), [fieldCoord](const Enemy *lhs, const Enemy *rhs) {
        double distanceLhs = Algorithms::calculateEuclideanDistance(lhs->getCenter(), Algorithms::fieldCoordToVector2fCentered(fieldCoord));
        double distanceRhs = Algorithms::calculateEuclideanDistance(rhs->getCenter(), Algorithms::fieldCoordToVector2fCentered(fieldCoord));
        return distanceLhs < distanceRhs;
        });
}

std::vector<Enemy *> Enemies::findAllInCircle(sf::Vector2f circleCenter, double searchRadius) {
    std::vector<Enemy *> enemiesInCircle;
    std::copy_if(enemies.begin(), enemies.end(), std::inserter(enemiesInCircle, enemiesInCircle.begin()), [searchRadius, circleCenter](const Enemy *enemy){
        double distance = Algorithms::calculateEuclideanDistance(enemy->getCenter(), circleCenter);
        return distance < searchRadius? true: false;
    });
    return enemiesInCircle;
    // for(auto &enemy: enemies){
    //     double distance = Algorithms::calculateEuclideanDistance(enemy->getCenter(), circleCenter);
    //     if(distance < searchRadius)
    //         enemiesInCircle.push_back(enemy);
    // }

    // return enemiesInCircle;
}

void Enemies::spawnInRandomPos(PathSearchField &pathSearchField, Bullets &bullets, DamageCircles &damageCircles){
    int position { rand() % (FIELD_LENGTH * 4) };
    if( position < 20 )
        append( new CasualEnemy({position, 0}, *this, pathSearchField, bullets, field, damageCircles));
    else if ( position < 40 )
        append( new CasualEnemy({19, position}, *this, pathSearchField, bullets, field, damageCircles));
    else if ( position < 60 )
        append( new CasualEnemy({position, 19}, *this, pathSearchField, bullets, field, damageCircles));
    else
        append( new CasualEnemy({0, position}, *this, pathSearchField, bullets, field, damageCircles));
} 