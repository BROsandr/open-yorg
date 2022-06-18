#include "GameClock.hpp"
#include "Enemy/Enemies.hpp"

GameClock::GameClock(PathSearchField &pathSearchField, Bullets &bullets, DamageCircles &damageCircles, Enemies &enemies) : pathSearchField(pathSearchField), bullets(bullets), damageCircles(damageCircles), enemies(enemies){
}

void GameClock::tick(){
    if(needToSwitch()){
        /* switchTime(); */
        if( isTimeToSpawn()) { 
            enemies.spawnInRandomPos(pathSearchField, bullets, damageCircles);
            restart();
            std::cout << "spawning" << std::endl;
        }
    }
}

bool GameClock::needToSwitch(){
    if((timeOfDay == TimeOfDay::day && getElapsedTime().asSeconds() > dayDuration) || 
       (timeOfDay == TimeOfDay::night && getElapsedTime().asSeconds() > nightDuration)){
            return true;
    }
    
    return false;
}

void GameClock::switchTime(){
    timeOfDay = static_cast<TimeOfDay>( (static_cast<int>(timeOfDay) + 1) & 1);
    restart();
}

GameClock::TimeOfDay GameClock::getTimeOfDay() const{
    return static_cast<TimeOfDay>(static_cast<int>(timeOfDay) & 1);
}

bool GameClock::isTimeToSpawn() {
    return getElapsedTime().asSeconds() > 10;
}