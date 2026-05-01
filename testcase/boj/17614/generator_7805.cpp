#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Special edge-case values
    vector<int> special = {1, 3, 9, 10, 14, 36, 100, 369, 999, 1000, 999999, 1000000};

    // Choose a scenario to diversify N
    int scenario = rnd.next(0, 4);
    int N = 1;
    if (scenario == 0) {
        // Pick a special edge-case
        N = rnd.any(special);
    } else if (scenario == 1) {
        // Small N: up to 10
        int maxSmall = rnd.next(1, 10);
        N = rnd.next(1, maxSmall);
    } else if (scenario == 2) {
        // Medium N: 11 to 1000
        N = rnd.next(11, 1000);
    } else if (scenario == 3) {
        // Large uniform N: 100000 to 1e6
        N = rnd.next(100000, 1000000);
    } else {
        // Large skewed towards upper bound
        // rnd.wnext(1000000, 2) gives max of 3 samples in [0,999999]
        N = rnd.wnext(1000000, 2) + 1;
    }

    // Ensure within [1, 1e6]
    N = max(1, min(N, 1000000));
    println(N);
    return 0;
}
