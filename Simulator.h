//
// Created by Sari Abed on 03/06/2021.
//

#ifndef NETWORKS_WET1_SIMULATOR_H
#define NETWORKS_WET1_SIMULATOR_H

#include <vector>
#include <random>
#include <cassert>
#include "Timer.h"

using std::vector;

class Simulator {
    Timer timer;
    double total_time;
    double lambda;
    double mu;
    vector<double> probabilities;
    vector<double> times;
    int msgs_accepted;
    int msgs_denied;
    int buffer_size;
    double final_time;


    static double generateExponential(double rate);
    void addMessageArrival();
    bool acceptOrDeny();
    void messageArrival();
    void addServiceEvent();
    void finishService();
    void callEventType( EventType type );

public:
    Simulator(double total_time, double lambda, double mu, vector<double> probabilities);
    void simulate();
    void printResults() const;


};


#endif //NETWORKS_WET1_SIMULATOR_H
