#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long boundedJitter(long long base, long long limit) {
    long long lo = max(1LL, base / 2);
    long long hi = min(limit, base * 2);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    const long long maxCost = 1000000000LL;

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 60);
    } else if (mode == 2) {
        vector<int> bases = {8, 16, 27, 32, 64, 81, 125, 243, 256, 512, 729, 1024};
        int base = rnd.any(bases);
        n = max(1, min(maxN, base + rnd.next(-2, 2)));
    } else if (mode == 3) {
        n = rnd.next(1000, 100000);
    } else if (mode == 4) {
        n = rnd.next(maxN - 1000, maxN);
    } else {
        n = rnd.next(1, maxN);
    }

    int costMode = rnd.next(0, 5);
    long long r, p;
    if (costMode == 0) {
        r = rnd.next(1LL, 20LL);
        p = rnd.next(1LL, 20LL);
    } else if (costMode == 1) {
        p = rnd.next(1LL, 1000LL);
        r = boundedJitter(p, maxCost);
    } else if (costMode == 2) {
        p = rnd.next(1LL, 1000LL);
        r = rnd.next(min(maxCost, p * 1000), maxCost);
    } else if (costMode == 3) {
        r = rnd.next(1LL, 1000LL);
        p = rnd.next(min(maxCost, r * 1000), maxCost);
    } else if (costMode == 4) {
        r = rnd.next(maxCost - 1000, maxCost);
        p = rnd.next(maxCost - 1000, maxCost);
    } else {
        r = rnd.next(1LL, maxCost);
        p = rnd.next(1LL, maxCost);
    }

    println(n, r, p);
    return 0;
}
