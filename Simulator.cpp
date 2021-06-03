//
// Created by Sari Abed on 03/06/2021.
//

#include "Simulator.h"

#include <utility>
#include <iostream>

using std::cout;
using std::endl;


Simulator::Simulator(double total_time, double lambda, double mu, vector<double> probabilities) : timer(),
                                                                                                  total_time(total_time), lambda(lambda), mu(mu), times(), msgs_accepted(0), msgs_denied(0),
                                                                                                  buffer_size(0), final_time(0) {
    this->probabilities = std::move(probabilities);
    for (int i=0; i< this->probabilities.size(); i++) {
        times.push_back(0);
    }

}

double Simulator::generateExponential(double rate) {
    std::random_device generator;
    std::exponential_distribution<double> exp_var(rate);

    return exp_var(generator);
}

void Simulator::addMessageArrival() {
    double arrival = generateExponential(lambda) + timer.getTime();
    if (arrival >= total_time) {
        return;
    }
    while ( !timer.addEvent(arrival, MESSAGE_ARRIVE) ) {
        arrival = generateExponential(lambda) + timer.getTime();
        if (arrival >= total_time) {
            return;
        }
    }
}

void Simulator::messageArrival() {
    if ( acceptOrDeny() ) {
        buffer_size++;
        msgs_accepted++;
        if (buffer_size == 1) {
            addServiceEvent();
        }
    } else {
        msgs_denied++;
    }

    addMessageArrival();
}

bool Simulator::acceptOrDeny() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    double x = probabilities[buffer_size];
    std::discrete_distribution<int> distribution({1-x, x});
    int number = distribution(generator);

    return ( number == 1 );
}

void Simulator::addServiceEvent() {
    assert( buffer_size > 0);

    double service_end = generateExponential(mu) + timer.getTime();
    while ( ! timer.addEvent(service_end, MESSAGE_SERVE) ) {
        service_end = generateExponential(mu) + timer.getTime();
    }
}

void Simulator::finishService() {
    buffer_size--;

    if (buffer_size > 0) {
        addServiceEvent();
    }
}

void Simulator::callEventType(EventType type) {
    if ( type == MESSAGE_SERVE ) {
        finishService();
    }
    else {
        assert(type == MESSAGE_ARRIVE);
        messageArrival();
    }
}

void Simulator::simulate() {
    addMessageArrival();
    double diff_time = 0;
    while ( !timer.isEmpty() ) {
        double old_time = timer.getTime();
        EventType event_type = timer.nextEvent();
        diff_time = timer.getTime() - old_time;

        times[buffer_size] += diff_time;

        callEventType(event_type);
    }

    final_time = timer.getTime();

    /******* PRINT RESULTS ********/

    // Y X T'
    cout << msgs_accepted << " " << msgs_denied << " " << final_time << " ";

    // Ti
    for ( auto t : times ) {
        cout << t << " ";
    }

    // Zi
    for ( auto t : times ) {
        cout << t/final_time << " ";
    }

    // Tw
    double total_wait_time = 0;
    for (int i=2; i<times.size(); i++) {
        /*
         * Since we have the times for each line length, in every length i, i-1
         * employees were waiting.
         */
        total_wait_time += times[i]* (i-1);
    }
    cout << total_wait_time/msgs_accepted << " ";

    //Ts
    /*
     * At all times, except when the queue was empty, we were
     * serving messages.
     */
    cout << (final_time - times[0]) / msgs_accepted << " ";

    //Lambda a
    cout << msgs_accepted / final_time;

}

void Simulator::printResults() const {
    // Y X T'
    cout << msgs_accepted << " " << msgs_denied << " " << final_time << " ";

    // Ti
    for ( auto t : times ) {
        cout << t << " ";
    }

    // Zi
    for ( auto t : times ) {
        cout << t/final_time << " ";
    }

    // Tw
    double total_wait_time = 0;
    for (int i=2; i<times.size(); i++) {
        /*
         * Since we have the times for each line length, in every length i, i-1
         * employees were waiting.
         */
        total_wait_time += times[i]* (i-1);
    }
    cout << total_wait_time/msgs_accepted << " ";

    //Ts
    /*
     * At all times, except when the queue was empty, we were
     * serving messages.
     */
    cout << (final_time - times[0]) / msgs_accepted << " ";

    //Lambda a
    cout << msgs_accepted / final_time;

}












