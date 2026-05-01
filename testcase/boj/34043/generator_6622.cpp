#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We only need to output a single integer N (1 <= N <= 100000).
    // Use weighted probabilities to cover edge cases and random ranges.
    double p = rnd.next(); // in [0,1)
    int N;
    if (p < 0.1) {
        // Very small edge case
        N = 1;
    } else if (p < 0.2) {
        // Next smallest edge
        N = 2;
    } else if (p < 0.4) {
        // Small N
        N = rnd.next(3, 10);
    } else if (p < 0.7) {
        // Moderate N
        N = rnd.next(11, 1000);
    } else if (p < 0.9) {
        // Larger N
        N = rnd.next(1001, 30000);
    } else {
        // Near maximum
        N = rnd.next(30001, 100000);
    }

    println(N);
    return 0;
}
