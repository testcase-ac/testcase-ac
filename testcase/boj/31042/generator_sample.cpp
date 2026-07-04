#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long clampCoord(long long value) {
    const long long kMaxCoordinate = 1LL << 60;
    return max(0LL, min(kMaxCoordinate, value));
}

long long nearPowerBoundary() {
    int bit = rnd.next(0, 60);
    long long base = 1LL << bit;
    long long delta = rnd.next(-3, 3);
    return clampCoord(base + delta);
}

long long coordinateForMode(int mode) {
    const long long kMaxCoordinate = 1LL << 60;

    if (mode == 0) {
        return rnd.next(0LL, 32LL);
    }
    if (mode == 1) {
        return nearPowerBoundary();
    }
    if (mode == 2) {
        int hiBit = rnd.next(1, 60);
        long long upper = (1LL << hiBit) - 1;
        return rnd.next(0LL, upper);
    }
    if (mode == 3) {
        return clampCoord(kMaxCoordinate - rnd.next(0LL, 16LL));
    }

    int bit = rnd.next(0, 60);
    long long anchor = 1LL << bit;
    long long span = min(127LL, kMaxCoordinate - anchor);
    return clampCoord(anchor + rnd.next(0LL, span));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 40);
    vector<pair<long long, long long>> cases;
    cases.reserve(n);

    vector<pair<long long, long long>> anchors = {
        {0, 0},
        {0, 1},
        {1, 0},
        {(1LL << 60), (1LL << 60)},
    };
    shuffle(anchors.begin(), anchors.end());

    for (auto [x, y] : anchors) {
        if ((int)cases.size() < n) {
            cases.push_back({x, y});
        }
    }

    while ((int)cases.size() < n) {
        int pattern = rnd.next(0, 5);
        long long x;
        long long y;

        if (pattern == 0) {
            int mode = rnd.next(0, 4);
            x = coordinateForMode(mode);
            y = coordinateForMode(mode);
        } else if (pattern == 1) {
            x = nearPowerBoundary();
            y = nearPowerBoundary();
        } else if (pattern == 2) {
            long long v = coordinateForMode(rnd.next(0, 4));
            long long d = rnd.next(-5, 5);
            x = clampCoord(v);
            y = clampCoord(v + d);
        } else if (pattern == 3) {
            x = coordinateForMode(3);
            y = coordinateForMode(rnd.next(0, 4));
        } else {
            x = coordinateForMode(rnd.next(0, 4));
            y = coordinateForMode(rnd.next(0, 4));
        }

        if (rnd.next(0, 1)) {
            swap(x, y);
        }
        cases.push_back({x, y});
    }

    shuffle(cases.begin(), cases.end());

    println(n);
    for (auto [x, y] : cases) {
        println(x, y);
    }

    return 0;
}
