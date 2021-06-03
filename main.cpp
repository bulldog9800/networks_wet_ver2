#include <iostream>
#include <string>
#include <vector>
#include "Simulator.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char** argv) {
    double total_allowed = stod(string(argv[1]));
    double lambda = stod(string(argv[2]));
    double mu = stod(string(argv[3]));

    vector<double> probabilities;
    assert(string(argv[4])=="1");
    assert(string(argv[argc-1])=="0");

    for (int i=4; i<argc; i++){
        probabilities.push_back(stod(string(argv[i])));
    }

    Simulator simulator(total_allowed, lambda, mu, probabilities);

    simulator.simulate();


    return 0;
}
