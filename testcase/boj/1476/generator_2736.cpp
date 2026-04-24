#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Maximum possible year by LCM of 15, 28, 19
    const int maxY = 15 * 28 * 19;  // 7980

    // Hyper-parameter to pick the year in different regimes
    double r = rnd.next();
    int y;
    if (r < 0.05) {
        // Edge case: the very first year
        y = 1;
    } else if (r < 0.10) {
        // Edge case: the maximum year before repeating
        y = maxY;
    } else if (r < 0.40) {
        // Small year for quick wrap-around tests
        y = rnd.next(2, 100);
    } else if (r < 0.70) {
        // Medium year
        y = rnd.next(101, 2000);
    } else {
        // Large year but not the absolute maximum
        y = rnd.next(2001, maxY - 1);
    }

    // Derive E, S, M from the chosen year
    int E = (y - 1) % 15 + 1;
    int S = (y - 1) % 28 + 1;
    int M = (y - 1) % 19 + 1;

    // Output the test case
    println(E, S, M);

    return 0;
}
