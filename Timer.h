//
// Created by Sari Abed on 03/06/2021.
//

#ifndef NETWORKS_WET1_TIMER_H
#define NETWORKS_WET1_TIMER_H

#include <cassert>
#include <map>
#include <utility>

enum EventType {MESSAGE_ARRIVE, MESSAGE_SERVE};

using std::map;
using std::pair;

typedef pair<double, EventType> pde;


class Timer {
    map<double, EventType> events;
    double current_time;
public:
    Timer();
    bool addEvent(double time, EventType type);
    double getTime() const;
    EventType nextEvent();
    bool isEmpty();
};




#endif //NETWORKS_WET1_TIMER_H
