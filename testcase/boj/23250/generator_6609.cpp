#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N in three categories: small, medium, large
    int cat = rnd.next(0, 2);
    int N;
    if (cat == 0) {
        // Small N
        N = rnd.next(1, 5);
    } else if (cat == 1) {
        // Medium N
        N = rnd.next(6, 20);
    } else {
        // Large N
        N = rnd.next(21, 60);
    }

    // Compute maximum moves for N disks: 2^N - 1
    unsigned long long maxK = (N < 64 ? (1ULL << N) : 0ULL) - 1;

    // Choose K in four patterns: first, last, middle, or random
    int kcat = rnd.next(0, 3);
    unsigned long long K;
    if (maxK == 0) {
        // N == 0 is impossible here, but guard just in case
        K = 1;
    } else if (kcat == 0) {
        K = 1;                        // first move
    } else if (kcat == 1) {
        K = maxK;                     // last move
    } else if (kcat == 2) {
        K = (maxK + 1) / 2;           // middle move
    } else {
        // random move in [1, maxK]
        K = rnd.next(1LL, (long long)maxK);
    }

    // Output the single test case
    println(N, K);

    return 0;
}
