#include "Clock.hpp"

void Clock::tick(){
    if(needToSwitch()){
        switchTime();
    }
}

bool Clock::needToSwitch(){
    if((timeOfDay == TimeOfDay::day && getElapsedTime().asSeconds() > DAY_DURATION) || 
       (timeOfDay == TimeOfDay::night && getElapsedTime().asSeconds() > NIGHT_DURATION)){
            return true;
    }
    
    return false;
}

void Clock::switchTime(){
    timeOfDay = static_cast<TimeOfDay>( (static_cast<int>(timeOfDay) + 1) & 1);
}

Clock::TimeOfDay Clock::getTimeOfDay() const{
    return static_cast<TimeOfDay>(static_cast<int>(timeOfDay) % 2);
}