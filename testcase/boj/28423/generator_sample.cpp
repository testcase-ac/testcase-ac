#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int clampValue(int x) {
    return max(1, min(100000, x));
}

pair<int, int> rangeAround(int center, int radius) {
    int l = clampValue(center - rnd.next(0, radius));
    int r = clampValue(center + rnd.next(0, radius));
    if (l > r) swap(l, r);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int l = 1;
    int r = 1;

    if (mode == 0) {
        l = r = rnd.next(1, 100000);
    } else if (mode == 1) {
        l = rnd.next(1, 100000);
        r = rnd.next(l, min(100000, l + rnd.next(0, 50)));
    } else if (mode == 2) {
        l = rnd.next(1, 100000);
        r = rnd.next(l, min(100000, l + rnd.next(100, 5000)));
    } else if (mode == 3) {
        vector<int> anchors = {1, 9, 10, 11, 50, 99, 100, 999, 1000, 9999, 10000, 99999, 100000};
        tie(l, r) = rangeAround(rnd.any(anchors), rnd.next(0, 25));
    } else if (mode == 4) {
        int len = rnd.next(1, 100000);
        l = rnd.next(1, 100000 - len + 1);
        r = l + len - 1;
    } else {
        vector<pair<int, int>> extremes = {{1, 1}, {1, 10}, {1, 100000}, {99990, 100000}, {100000, 100000}};
        tie(l, r) = rnd.any(extremes);
    }

    println(l, r);
    return 0;
}
