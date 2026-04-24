#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    // Predefined ranges for distance, speed, consumption
    vector<pair<int,int>> distRanges = {{1,100}, {100,1000}, {1000,10000}};
    vector<pair<int,int>> speedRanges = {{1,10}, {10,100}, {100,1000}};
    vector<pair<int,int>> consRanges  = {{1,10}, {10,100}, {100,1000}};

    for (int tc = 0; tc < T; tc++) {
        // Small N
        int N = rnd.next(1, 10);
        // Choose distance scale
        auto dr = rnd.any(distRanges);
        int D = rnd.next(dr.first, dr.second);
        println(N, D);

        for (int i = 0; i < N; i++) {
            // Choose speed and consumption from categories
            auto sr = rnd.any(speedRanges);
            int v = rnd.next(sr.first, sr.second);
            auto cr = rnd.any(consRanges);
            int c = rnd.next(cr.first, cr.second);

            // Compute exact needed fuel = c * D / v
            double needed = (double)c * D / v;
            double f_lo = floor(needed);
            double f_hi = ceil(needed);

            // Decide how to pick fuel amount: random or edge-case
            int pickType = rnd.next(0, 2);
            int f;
            if (pickType == 1) {
                // floor case
                f = (int)f_lo;
                if (f < 1) f = 1;
                if (f > 1000) f = 1000;
            } else if (pickType == 2) {
                // ceil case
                f = (int)f_hi;
                if (f < 1) f = 1;
                if (f > 1000) f = 1000;
            } else {
                // fully random
                f = rnd.next(1, 1000);
            }

            println(v, f, c);
        }
    }

    return 0;
}
