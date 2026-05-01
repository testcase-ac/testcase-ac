#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate a single test case
    // Choose N in [4,7] with two size classes for variability
    int sizeClass = rnd.next(0, 1);
    int N = (sizeClass == 0 ? rnd.next(4, 5) : rnd.next(6, 7));

    // Choose a distribution type for grid values
    // 0: full range [-1e6,1e6], 1: small [-10,10], 2: positive [0,1000],
    // 3: negative [-1000,0], 4: all zeros
    int dt = rnd.next(0, 4);
    int lo, hi;
    if (dt == 0) {
        lo = -1000000; hi = 1000000;
    } else if (dt == 1) {
        lo = -10; hi = 10;
    } else if (dt == 2) {
        lo = 0; hi = 1000;
    } else if (dt == 3) {
        lo = -1000; hi = 0;
    } else {
        lo = hi = 0;
    }

    // Build the grid
    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = rnd.next(lo, hi);
        }
    }

    // Output the test case
    println(N);
    for (auto &row : grid) {
        println(row);
    }
    // Termination line
    println(0);

    return 0;
}
