#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int mode;

    if (argc >= 2) {
        mode = atoi(argv[1]) % 5;
        if (mode < 0) mode += 5;
    } else {
        mode = rnd.next(0, 4);
    }

    switch (mode) {
        case 0: {
            // Extreme small or large within constraints
            if (rnd.next(0, 1) == 0) N = 1;
            else N = 10;
            break;
        }
        case 1: {
            // Very small values for easy manual checking
            N = rnd.next(1, 4); // 1..3
            break;
        }
        case 2: {
            // Medium range values
            N = rnd.next(3, 8); // 3..8
            break;
        }
        case 3: {
            // Fibonacci-like "interesting" values
            int fibs[] = {1, 2, 3, 5, 8};
            N = fibs[rnd.next(0, 4)];
            break;
        }
        case 4: {
            // Mix of primes and composites
            vector<int> primes = {2, 3, 5, 7};
            vector<int> comps  = {4, 6, 8, 9, 10};
            if (rnd.next(0, 1) == 0) N = rnd.any(primes);
            else N = rnd.any(comps);
            break;
        }
        default: {
            N = 1; // Fallback (should not be reached)
            break;
        }
    }

    println(N);
    return 0;
}
