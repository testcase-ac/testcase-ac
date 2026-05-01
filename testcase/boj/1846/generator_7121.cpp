#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // We will randomly choose among several size regimes to increase variability
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        // Edge impossible case
        N = 3;
    } else if (p < 0.3) {
        // Small boards
        N = rnd.next(4, 10);
    } else if (p < 0.6) {
        // Moderate boards
        N = rnd.next(11, 100);
    } else if (p < 0.8) {
        // Larger but still hand-verifiable boards
        N = rnd.next(101, 1000);
    } else {
        // Very large boards, biased towards the maximum
        // rnd.wnext(100000, 3) returns max of 4 samples in [0,99999]
        N = rnd.wnext(100000, 3) + 1;
    }
    // Ensure constraints
    N = max(N, 3);
    N = min(N, 100000);
    println(N);
    return 0;
}
