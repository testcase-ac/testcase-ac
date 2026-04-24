#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters
    double large_n_prob = rnd.next(0.3, 0.7); // Probability of generating a test case with large N
    int a_max = 100000;
    int b_max = 100000;
    int n_max = 1000000;

    int a, b, n;

    if (rnd.next() < large_n_prob) {
        // Generate a test case with a potentially large N
        a = rnd.next(1, a_max);
        b = rnd.next(1, b_max);
        n = rnd.next(n_max / 2, n_max); // N is in the upper half of its range
    } else {
        // Generate a test case with small A, B, and N for manual verification
        a = rnd.next(1, 100);
        b = rnd.next(1, 100);
        n = rnd.next(1, 10);
    }

    cout << a << " " << b << " " << n << endl;

    return 0;
}
