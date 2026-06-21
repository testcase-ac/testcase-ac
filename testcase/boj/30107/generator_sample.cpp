#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static int clampValue(int x) {
    return max(1, min(500000, x));
}

static int randomWeight() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 1;
    if (mode == 1) return 500000;
    if (mode == 2) return rnd.next(1, 20);
    if (mode == 3) return rnd.next(499980, 500000);
    return rnd.next(1, 500000);
}

static pair<int, int> randomWeights() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        int x = randomWeight();
        return {x, x};
    }
    if (mode == 1) return {1, randomWeight()};
    if (mode == 2) return {500000, randomWeight()};
    return {randomWeight(), randomWeight()};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> nValues = {1, 2, 3, 4, 7, 8, 15, 16, 31, 32, 10000, 499999, 500000};

    int base = 1 << rnd.next(1, 19);
    for (int delta = -2; delta <= 2; ++delta) {
        nValues.push_back(clampValue(base + delta));
        nValues.push_back(clampValue(base - 1 + delta));
    }

    int smallCount = rnd.next(5, 12);
    for (int i = 0; i < smallCount; ++i) nValues.push_back(rnd.next(1, 128));

    int mediumCount = rnd.next(3, 8);
    for (int i = 0; i < mediumCount; ++i) nValues.push_back(rnd.next(1, 500000));

    int t = rnd.next(12, min(60, (int)nValues.size()));
    shuffle(nValues.begin(), nValues.end());

    println(t);
    for (int i = 0; i < t; ++i) {
        auto weights = randomWeights();
        println(nValues[i], weights.first, weights.second);
    }

    return 0;
}
