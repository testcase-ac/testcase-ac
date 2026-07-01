#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long clampLimit(long long value) {
    return max(1LL, min(LIMIT, value));
}

long long pow2(int exponent) {
    return 1LL << exponent;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> anchors = {
        1,
        2,
        3,
        4,
        7,
        15,
        31,
        63,
        255,
        1023,
        1024,
        LIMIT
    };

    int extraAnchors = rnd.next(4, 8);
    for (int i = 0; i < extraAnchors; ++i) {
        int exponent = rnd.next(1, 59);
        long long base = pow2(exponent);
        long long delta = rnd.next(-3LL, 3LL);
        anchors.push_back(clampLimit(base + delta));
    }

    shuffle(anchors.begin(), anchors.end());

    int caseCount = rnd.next(12, 24);
    for (int caseId = 0; caseId < caseCount; ++caseId) {
        int mode = rnd.next(0, 5);
        long long lo, hi;

        if (mode == 0) {
            lo = rnd.any(anchors);
            hi = lo;
        } else if (mode == 1) {
            long long center = rnd.any(anchors);
            long long radius = rnd.next(0LL, 12LL);
            lo = clampLimit(center - radius);
            hi = clampLimit(center + radius);
        } else if (mode == 2) {
            lo = rnd.next(1LL, 2000LL);
            hi = rnd.next(lo, min(LIMIT, lo + rnd.next(0LL, 200LL)));
        } else if (mode == 3) {
            long long span = rnd.next(0LL, 1000000LL);
            lo = rnd.next(1LL, LIMIT - span);
            hi = lo + span;
        } else if (mode == 4) {
            hi = LIMIT - rnd.next(0LL, 1000LL);
            lo = hi - rnd.next(0LL, 1000LL);
        } else {
            int exponent = rnd.next(1, 59);
            long long allOnes = pow2(exponent) - 1;
            lo = clampLimit(allOnes - rnd.next(0LL, 8LL));
            hi = clampLimit(allOnes + rnd.next(0LL, 8LL));
        }

        if (lo > hi) {
            swap(lo, hi);
        }

        int x = rnd.next(0, 10);
        println(lo, hi, x);
    }

    println(0, 0, 0);
    return 0;
}
