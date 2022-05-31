#include "GameElements.hpp"
#include "Enemy/Enemies.hpp"

GameElements::GameElements() : enemies(field) { }

void GameElements::tick(){
    field.tick();
    resourceBalls.tick();
    enemies.update();
    enemies.draw();
    // resourceBalls.tick();
    bullets.tick();
    damageCircles.tick();
}