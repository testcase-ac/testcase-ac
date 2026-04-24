#include "testlib.h"
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const long long MAXN = 500000000000LL;

    int scenario = rnd.next(0, 3);
    long long N;
    if (scenario == 0) {
        // Small N: hand-checkable
        N = rnd.next(1LL, 10LL);
    } else if (scenario == 1) {
        // Moderate N
        N = rnd.next(1LL, 1000000LL);
    } else if (scenario == 2) {
        // Very large N near the upper bound
        N = rnd.next(100000000000LL, MAXN);
    } else {
        // Biased distribution over [1, MAXN]
        int alpha = rnd.next(1, 5);
        double x = rnd.next();
        if (rnd.next(0, 1) == 0) {
            // bias towards smaller values
            x = pow(x, alpha);
        } else {
            // bias towards larger values
            x = 1.0 - pow(1.0 - x, alpha);
        }
        N = 1 + (long long)floor(x * MAXN);
        if (N < 1) N = 1;
        if (N > MAXN) N = MAXN;
    }

    println(N);
    return 0;
}
