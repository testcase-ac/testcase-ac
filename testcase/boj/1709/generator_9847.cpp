#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hand-picked interesting even N values (covering small, medium, and near-boundary cases)
    vector<int> specials = {
        2, 4, 6, 8, 10, 12, 14, 16, 18, 20,   // very small
        26, 34, 50, 58,                       // includes examples and small primes-related radii
        98, 100, 130,                         // medium-small
        256, 1000, 2210,                      // with various factorizations
        99999998, 100000000,                  // large, mid-range
        149999998, 150000000                  // near and at upper bound
    };

    int mode = rnd.next(0, 4); // choose generation strategy
    int N;

    if (mode == 0) {
        // Directly pick one of the special values
        N = rnd.any(specials);
    } else if (mode == 1) {
        // Tiny random even N in [2, 40]
        N = 2 * rnd.next(1, 20);
    } else if (mode == 2) {
        // Medium random even N roughly in [42, 20000]
        int low = 21, high = 10000;
        N = 2 * rnd.next(low, high);
    } else if (mode == 3) {
        // Large N biased towards the upper end of the range
        // k in [1, 75_000_000], bias to large via wnext
        int k = rnd.wnext(75000000, 3) + 1;
        N = 2 * k;
    } else {
        // Uniform random even N over the whole valid range
        int k = rnd.next(1, 75000000);
        N = 2 * k;
    }

    // Safety: clamp to constraints and ensure even
    if (N < 2) N = 2;
    if (N > 150000000) N = 150000000;
    if (N % 2 == 1) {
        if (N < 150000000) N++;  // adjust up if possible
        else N--;                // otherwise adjust down
    }
    if (N < 2) N = 2;           // re-assert lower bound

    println(N);

    return 0;
}
