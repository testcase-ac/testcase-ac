#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for generating the input
    int min_n = 1;
    int max_n = 100; // Reduced max_n to 100 to ensure small test cases for manual verification

    // Introduce some randomization
    double prob_small_n = rnd.next(0.0, 1.0); // Probability of generating a small n
    int n;

    if (prob_small_n < 0.7) {
        // Generate smaller n with higher probability
        int max_small_n = rnd.next(10,50);
        n = rnd.next(min_n, max_small_n);
    } else {
        // Otherwise generate from full range
        n = rnd.next(min_n, max_n);
    }


    println(n);

    return 0;
}
