#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N distribution: tiny, small, medium, large
    double u = rnd.next();
    int N;
    if (u < 0.2) {
        N = rnd.next(2, 10);
    } else if (u < 0.5) {
        N = rnd.next(10, 100);
    } else if (u < 0.8) {
        N = rnd.next(100, 500);
    } else {
        N = rnd.next(500, 1000);
    }
    // Hyper-parameter for K distribution: early, middle, late removals
    int lo, hi;
    double v = rnd.next();
    if (v < 0.33 && N > 3) {
        lo = 1;
        hi = max(1, N / 3);
    } else if (v < 0.66 && N > 3) {
        lo = max(1, N / 3 + 1);
        hi = max(lo, (N * 2) / 3);
    } else {
        lo = max(1, (N * 2) / 3 + 1);
        hi = N - 1;
    }
    // Fallback if range invalid
    if (lo > hi) {
        lo = 1;
        hi = N - 1;
    }
    int K = rnd.next(lo, hi);
    println(N, K);
    return 0;
}
