#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate N between 1 and 20, biased towards small or large by wnext
    int N = rnd.wnext(20, rnd.next(-1, 1)) + 1;
    // Probability to issue a removal (0) operation, biased by wnext
    double removeProb = rnd.wnext(101, rnd.next(-2, 2)) / 100.0;

    vector<long long> ops;
    ops.reserve(N);
    for (int i = 0; i < N; i++) {
        // Decide removal vs insertion
        if (rnd.next() < removeProb) {
            ops.push_back(0);
        } else {
            long long x;
            // Occasionally pick an extreme value
            if (rnd.next(0, 9) == 0) {
                x = (rnd.next(0, 1) == 0 ? 2147483647LL : -2147483647LL);
            } else {
                // Generate small magnitudes [1..9], biased towards small
                int mag = rnd.wnext(10, -2);
                if (mag == 0) mag = 1;
                x = mag * (rnd.next(0, 1) ? 1 : -1);
            }
            ops.push_back(x);
        }
    }

    // Output
    println(N);
    for (auto x : ops) println(x);
    return 0;
}
