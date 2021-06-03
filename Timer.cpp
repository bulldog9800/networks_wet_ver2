//
// Created by Sari Abed on 03/06/2021.
//

#include "Timer.h"

Timer::Timer() : current_time(0){

}

bool Timer::addEvent(double time, EventType type) {
    auto it = events.find(time);
    if (it != events.end() ) {
        // Event already exists in system
        return false;
    }
    events.insert(pde(time, type));
    return true;
}

double Timer::getTime() const {
    return current_time;
}

EventType Timer::nextEvent() {
    assert ( !events.empty() );
    auto it = events.begin();
    current_time = (*it).first;
    EventType type = (*it).second;
    events.erase(it);

    return type;
}

bool Timer::isEmpty() {
    return events.empty();
}



