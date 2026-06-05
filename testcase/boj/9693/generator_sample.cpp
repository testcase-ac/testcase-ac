#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int clampN(int n) {
    return max(5, min(1000000, n));
}

int nearPowerOfFive() {
    vector<int> powers;
    for (int p = 5; p <= 1000000; p *= 5) {
        powers.push_back(p);
    }

    int base = rnd.any(powers);
    int delta = rnd.next(-8, 8);
    return clampN(base + delta);
}

int randomN(int mode) {
    if (mode == 0) {
        return rnd.next(5, 40);
    }
    if (mode == 1) {
        return nearPowerOfFive();
    }
    if (mode == 2) {
        vector<int> anchors = {5, 10, 24, 25, 26, 124, 125, 126, 624, 625,
                               626, 3124, 3125, 3126, 999999, 1000000};
        int value = rnd.any(anchors);
        if (rnd.next(0, 2) == 0) {
            value += rnd.next(-3, 3);
        }
        return clampN(value);
    }
    if (mode == 3) {
        return rnd.next(5, 1000000);
    }
    return rnd.next(900000, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int t;
    if (mode == 0) {
        t = rnd.next(1, 6);
    } else if (mode == 1) {
        t = rnd.next(4, 12);
    } else if (mode == 2) {
        t = rnd.next(6, 16);
    } else {
        t = rnd.next(1, 10);
    }

    vector<int> cases;
    for (int i = 0; i < t; ++i) {
        cases.push_back(randomN(mode));
    }

    if (rnd.next(0, 3) == 0) {
        shuffle(cases.begin(), cases.end());
    }

    for (int n : cases) {
        println(n);
    }
    println(0);

    return 0;
}
