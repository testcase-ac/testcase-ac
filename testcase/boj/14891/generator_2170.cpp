#include "testlib.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters
    int K = rnd.next(1, 5); // Number of rotations
    double prob_S = rnd.next(0.2, 0.8); // Probability of a tooth being S pole

    // Generate initial states of the gears
    vector<string> gears(4);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            gears[i] += (rnd.next() < prob_S) ? '1' : '0';
        }
    }

    // Generate rotation instructions
    vector<pair<int, int>> rotations(K);
    for (int i = 0; i < K; ++i) {
        rotations[i].first = rnd.next(1, 4); // Gear number
        rotations[i].second = rnd.next(0, 1) * 2 - 1; // Direction (1 or -1)
    }

    // Output the test case
    for (const string& gear : gears) {
        println(gear);
    }

    println(K);
    for (const auto& rotation : rotations) {
        println(rotation.first, rotation.second);
    }

    return 0;
}
