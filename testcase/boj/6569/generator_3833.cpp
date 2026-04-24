#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(3, 10);
    // probability to pick extremes (1 or 11)
    const double edgeProb = 0.3;
    vector<int> extremes = {1, 11};

    for (int i = 0; i < T; i++) {
        int h = rnd.next() < edgeProb ? rnd.any(extremes) : rnd.next(1, 11);
        int w = rnd.next() < edgeProb ? rnd.any(extremes) : rnd.next(1, 11);
        // random orientation swap for diversity
        if (rnd.next() < 0.5) swap(h, w);
        println(h, w);
    }
    // termination line
    println(0, 0);
    return 0;
}
