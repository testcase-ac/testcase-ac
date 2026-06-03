#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int smallCoord() {
    int span = rnd.next(1, 25);
    return rnd.next(-span, span);
}

int farCoord() {
    vector<int> anchors = {-100000000, -10000000, -1000, 0, 1000, 10000000, 100000000};
    int base = rnd.any(anchors);
    int delta = rnd.next(-20, 20);
    long long value = (long long)base + delta;
    value = max(-100000000LL, min(100000000LL, value));
    return (int)value;
}

pair<int, int> makeCase(int mode) {
    if (mode == 0) {
        return {smallCoord(), smallCoord()};
    }

    if (mode == 1) {
        int sign = rnd.next(0, 1) ? 1 : -1;
        int a = sign * rnd.next(0, 30);
        int b = sign * rnd.next(0, 30);
        return {a, b};
    }

    if (mode == 2) {
        int left = -rnd.next(0, 40);
        int right = rnd.next(0, 40);
        if (rnd.next(0, 1)) return {left, right};
        return {right, left};
    }

    if (mode == 3) {
        int a = rnd.next(-50, 50);
        int b = rnd.any(vector<int>{-50, -25, -10, 0, 10, 25, 50});
        return {a, b};
    }

    return {farCoord(), farCoord()};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 4) {
        n = rnd.next(1, 8);
    } else {
        n = rnd.next(1, 20);
    }

    vector<pair<int, int>> trips;
    trips.reserve(n);

    int sharedB = smallCoord();
    for (int i = 0; i < n; ++i) {
        int rowMode = mode;
        if (mode == 3 && rnd.next(0, 2) == 0) {
            trips.push_back({smallCoord(), sharedB});
        } else {
            trips.push_back(makeCase(rowMode));
        }
    }

    shuffle(trips.begin(), trips.end());

    println(n);
    for (auto trip : trips) {
        println(trip.first, trip.second);
    }

    return 0;
}
