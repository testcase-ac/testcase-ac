#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: small dimensions with N ≤ M
    int N = rnd.next(1, 10);
    int M = rnd.next(N, 10);

    // Total seats
    int T = N * M;

    // Hyper-parameter: pick K from various distributions
    int mode = rnd.next(0, 4);
    int K;
    if (mode == 0) {
        // Very first seat
        K = 0;
    } else if (mode == 1) {
        // Very last seat
        K = T - 1;
    } else if (mode == 2) {
        // Skew toward lower indices
        K = rnd.wnext(T, -2);
    } else if (mode == 3) {
        // Skew toward higher indices
        K = rnd.wnext(T, 2);
    } else {
        // Uniform anywhere
        K = rnd.next(0, T - 1);
    }

    // Output a single test case
    println(N, M, K);

    return 0;
}
