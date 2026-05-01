#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We will output a single N in [1, 1e18], choosing among several categories
    int category = rnd.next(0, 3);
    long long N;

    if (category == 0) {
        // Edge and small tricky cases
        vector<long long> preset = {
            1LL, 2LL, 3LL, 4LL, 5LL, 6LL, 7LL, 8LL,
            15LL, 16LL, 17LL, 18LL, 31LL, 32LL, 33LL
        };
        N = rnd.any(preset);
    }
    else if (category == 1) {
        // Small random
        N = rnd.next(1LL, 100LL);
    }
    else if (category == 2) {
        // Medium random
        N = rnd.next(101LL, 1000000LL);
    }
    else {
        // Large and edge large
        vector<long long> largeVals = {
            1000000000000000000LL,
            1000000000000000000LL - 1,
            999999999999999989LL
        };
        // add one additional random large
        largeVals.push_back(rnd.next(1LL, 1000000000000000000LL));
        N = rnd.any(largeVals);
    }

    println(N);
    return 0;
}
