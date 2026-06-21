#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

int clampCount(int value) {
    return max(1, min(100, value));
}

array<int, 3> makeCase(int mode) {
    if (mode == 0) {
        int x = rnd.next(1, 12);
        return {x, x, x};
    }

    if (mode == 1) {
        int base = rnd.next(1, 20);
        return {
            clampCount(base + rnd.next(-2, 2)),
            clampCount(base + rnd.next(-2, 2)),
            clampCount(base + rnd.next(-2, 2))
        };
    }

    if (mode == 2) {
        int big = rnd.next(20, 100);
        int small1 = rnd.next(1, 8);
        int small2 = rnd.next(1, 8);
        vector<int> values = {big, small1, small2};
        shuffle(values.begin(), values.end());
        return {values[0], values[1], values[2]};
    }

    if (mode == 3) {
        vector<int> values = {
            rnd.next(1, 5),
            rnd.next(90, 100),
            rnd.next(90, 100)
        };
        shuffle(values.begin(), values.end());
        return {values[0], values[1], values[2]};
    }

    if (mode == 4) {
        vector<int> values = {1, rnd.next(1, 100), rnd.next(1, 100)};
        shuffle(values.begin(), values.end());
        return {values[0], values[1], values[2]};
    }

    return {rnd.next(1, 100), rnd.next(1, 100), rnd.next(1, 100)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        auto values = makeCase(mode);
        println(values[0], values[1], values[2]);
    }

    return 0;
}
