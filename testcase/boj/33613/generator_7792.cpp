#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int pickPos(int N) {
    // modes: 0 = near top/left edge, 1 = near bottom/right edge, 2 = anywhere
    int mode = rnd.next(0, 2);
    int lo, hi;
    if (mode == 0) {
        lo = 1; hi = min(3, N);
    } else if (mode == 1) {
        lo = max(1, N - 2); hi = N;
    } else {
        lo = 1; hi = N;
    }
    if (lo > hi) {
        lo = 1; hi = N;
    }
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose N in small, medium, or large range
    int tier = rnd.next(1, 3);
    int N;
    if (tier == 1) {
        // small sizes
        N = rnd.next(3, 10);
    } else if (tier == 2) {
        // medium sizes
        N = rnd.next(11, 100);
    } else {
        // large sizes
        // bias towards very large occasionally
        if (rnd.next(0, 4) == 0) {
            // very large
            N = rnd.next(50000, 100000);
        } else {
            // moderately large
            N = rnd.next(101, 49999);
        }
    }
    int R = pickPos(N);
    int C = pickPos(N);
    println(N);
    println(R, C);
    return 0;
}
