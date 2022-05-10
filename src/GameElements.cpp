#include "GameElements.hpp"

void GameElements::tick(){
    field.tick();
    resourceBalls.tick();
    enemies.update();
    enemies.draw();
    // resourceBalls.tick();
    bullets.tick();
    damageCircles.tick();
}