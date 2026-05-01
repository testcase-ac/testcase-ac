#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // N in [2,20], skewed towards smaller values
    int N = rnd.wnext(19, -2) + 2;

    // Choose A with some chance of extreme (1 or N-1), else uniform
    int A;
    if (rnd.next() < 0.3) {
        A = rnd.any(vector<int>{1, N-1});
    } else {
        A = rnd.next(1, N-1);
    }
    int B = N - A;

    println(N, A, B);

    // Choose magnitude class for prices
    int lo, hi;
    double magProb = rnd.next();
    if (magProb < 0.2) {
        lo = 1; hi = 10;
    } else if (magProb < 0.5) {
        lo = 1; hi = 1000;
    } else {
        lo = 1; hi = 1000000000;
    }

    // Generate p_i, q_i with optional bias and occasional ties
    for (int i = 0; i < N; i++) {
        int p, q;
        double mode = rnd.next();
        if (mode < 0.33) {
            // independent random
            p = rnd.next(lo, hi);
            q = rnd.next(lo, hi);
        } else if (mode < 0.66) {
            // bias p <= q
            p = rnd.next(lo, hi);
            int maxDelta = hi - p;
            int d = maxDelta > 0 ? rnd.next(0, maxDelta) : 0;
            q = p + d;
        } else {
            // bias p >= q
            q = rnd.next(lo, hi);
            int maxDelta = hi - q;
            int d = maxDelta > 0 ? rnd.next(0, maxDelta) : 0;
            p = q + d;
        }
        // occasional tie
        if (rnd.next() < 0.1) {
            q = p;
        }
        println(p, q);
    }

    return 0;
}
