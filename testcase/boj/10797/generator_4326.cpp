#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Date digit
    int d = rnd.next(0, 9);

    // Choose number of matches k with some skewed distribution
    double mode = rnd.next();
    int k;
    if (mode < 0.2) {
        k = 0;
    } else if (mode < 0.4) {
        k = 5;
    } else if (mode < 0.6) {
        k = rnd.next(1, 2);
    } else if (mode < 0.8) {
        k = rnd.next(3, 4);
    } else {
        k = rnd.next(0, 5);
    }

    // Build the 5 car digits, k equal to d, rest different
    vector<int> cars;
    for (int i = 0; i < k; ++i) {
        cars.push_back(d);
    }
    for (int i = 0; i < 5 - k; ++i) {
        int x;
        do {
            x = rnd.next(0, 9);
        } while (x == d);
        cars.push_back(x);
    }

    // Shuffle for randomness
    shuffle(cars.begin(), cars.end());

    // Output
    println(d);
    println(cars);

    return 0;
}
