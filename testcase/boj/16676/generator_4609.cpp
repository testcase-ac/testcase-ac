#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for diversity: choose type of N
    int mode = rnd.next(0, 2);
    long long N;

    if (mode == 0) {
        // Small N for hand checking
        N = rnd.next(0LL, 20LL);
    } else if (mode == 1) {
        // Medium N
        N = rnd.next(0LL, 1000LL);
    } else {
        // Large N: mostly uniform, sometimes near power-of-ten boundaries
        if (rnd.next(0, 1) == 0) {
            int d = rnd.next(1, 9);
            long long p = 1;
            for (int i = 0; i < d; i++) p *= 10;
            // N near p (within 0..100)
            long long deltaMax = min(p, 100LL);
            long long delta = rnd.next(0LL, deltaMax);
            N = p - delta;
            if (N < 0) N = 0;
        } else {
            N = rnd.next(0LL, 1000000000LL);
        }
    }

    // Output a single test case: N
    println(N);
    return 0;
}
