#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases, small enough for manual checking but variable
    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; i++) {
        // Choose gap category by probability to get small/medium/large/extreme gaps
        double p = rnd.next();
        int lo, hi;
        if (p < 0.2) {
            // Extreme large gap
            lo = 100001;
            hi = 10000000;
        } else if (p < 0.5) {
            // Large gap
            lo = 101;
            hi = 100000;
        } else if (p < 0.8) {
            // Medium gap
            lo = 6;
            hi = 100;
        } else {
            // Small gap (but at least 2 so L < S < R always possible)
            lo = 2;
            hi = 5;
        }
        // Cap to global max difference
        hi = min(hi, 100000000);
        int gap = rnd.next(lo, hi);

        // Choose L so that L>=-1e8 and R=L+gap <=1e8
        int maxL = 100000000 - gap;
        int L = rnd.next(-100000000, maxL);
        int R = L + gap;

        // Choose S strictly between L and R
        int S = rnd.next(L + 1, R - 1);

        println(L, R, S);
    }
    return 0;
}
