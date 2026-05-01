#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a category to expose edge cases and varied sizes
    int category = rnd.next(0, 3);
    long long N;
    switch (category) {
        case 0:
            // smallest edge case
            N = 1;
            break;
        case 1:
            // small N for brute-force or simple checks
            N = rnd.next(2, 10);
            break;
        case 2:
            // moderate N to test DP or formulas
            N = rnd.next(11, 1000);
            break;
        case 3:
        default:
            // large N to test performance and overflow handling
            if (rnd.next(0, 1) == 0) {
                // moderately large
                N = rnd.next(1000, 1000000);
            } else {
                // very large up to maximum constraint
                N = rnd.next(1000000, 1000000000);
            }
            break;
    }

    // Output the single test case
    println(N);
    return 0;
}
