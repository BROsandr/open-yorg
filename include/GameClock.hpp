#pragma once

#include <SFML/System/Clock.hpp>
/* #include <SFML/System/Time.hpp> */

#include "ValuesAndTypes.hpp"

class PathSearchField;
class Bullets;
class DamageCircles;
class Enemies;

class GameClock: sf::Clock{
public:
    enum class TimeOfDay{
        night,
        day
    };

    void tick();
    TimeOfDay getTimeOfDay() const;
    GameClock(PathSearchField &pathSearchField, Bullets &bullets, DamageCircles &damageCircles, Enemies &enemies);
    bool isTimeToSpawn();

private:
    /* sf::Time time = sf::seconds(NONE); */
    TimeOfDay timeOfDay = TimeOfDay::day;
    const int dayDuration { 20 };
    const int nightDuration { 20 };
    PathSearchField &pathSearchField;
    Bullets &bullets;
    DamageCircles &damageCircles;
    Enemies &enemies;
    
    void switchTime();
    bool needToSwitch();
};