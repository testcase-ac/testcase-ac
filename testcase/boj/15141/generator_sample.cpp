#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

long long chooseFeasibleN(int h, int w) {
    int rowParts = (h + 1) / 2;
    int colParts = (w + 1) / 2;
    int a = rnd.next(1, rowParts);
    int b = rnd.next(1, colParts);
    return 1LL * a * b;
}

long long chooseLikelyImpossibleN(int h, int w) {
    int rowParts = (h + 1) / 2;
    int colParts = (w + 1) / 2;
    long long maxParts = 1LL * rowParts * colParts;
    vector<long long> candidates;

    if (maxParts < 1000000000LL) candidates.push_back(maxParts + 1);
    candidates.push_back(1000000000LL);

    for (int delta = 1; delta <= 5; ++delta) {
        if (maxParts + delta <= 1000000000LL) candidates.push_back(maxParts + delta);
    }

    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h, w;
    long long n;

    if (mode == 0) {
        h = rnd.next(1, 8);
        w = rnd.next(1, 8);
        n = chooseFeasibleN(h, w);
    } else if (mode == 1) {
        h = rnd.any(vector<int>{1, 2, 3, 99, 100});
        w = rnd.any(vector<int>{1, 2, 3, 99, 100});
        n = chooseFeasibleN(h, w);
    } else if (mode == 2) {
        h = rnd.next(1, 20);
        w = rnd.next(1, 20);
        n = chooseLikelyImpossibleN(h, w);
    } else if (mode == 3) {
        h = rnd.next(1, 100);
        w = rnd.next(1, 100);
        n = rnd.next(1LL, 1000000000LL);
    } else if (mode == 4) {
        h = rnd.next(90, 100);
        w = rnd.next(90, 100);
        n = chooseFeasibleN(h, w);
    } else {
        h = rnd.next(1, 100);
        w = rnd.next(1, 100);
        long long maxParts = 1LL * ((h + 1) / 2) * ((w + 1) / 2);
        n = rnd.next(max(1LL, maxParts - 5), min(1000000000LL, maxParts + 5));
    }

    println(h, w, n);
    return 0;
}
