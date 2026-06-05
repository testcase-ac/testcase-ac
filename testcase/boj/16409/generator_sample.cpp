#include "testlib.h"
#include <algorithm>
#include <utility>

using namespace std;

const int LIMIT = 10000000;

pair<int, int> intervalNear(int center, int radius) {
    int lo = max(1, center - radius);
    int hi = min(LIMIT, center + radius);
    int a = rnd.next(lo, hi);
    int b = rnd.next(a, hi);
    return {a, b};
}

pair<int, int> intervalWithWidth(int lo, int hi, int maxWidth) {
    int a = rnd.next(lo, hi);
    int b = rnd.next(a, min(hi, a + maxWidth));
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    pair<int, int> first;
    pair<int, int> second;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        first = intervalWithWidth(1, 30, 8);
        second = intervalWithWidth(1, 30, 8);
    } else if (mode == 1) {
        int x = rnd.next(1, LIMIT);
        int y = rnd.next(1, LIMIT);
        first = {x, x};
        second = {y, y};
    } else if (mode == 2) {
        first = intervalNear(rnd.next(1, 2000), rnd.next(0, 40));
        second = intervalNear(rnd.next(1, 2000), rnd.next(0, 40));
    } else if (mode == 3) {
        first = intervalNear(LIMIT - rnd.next(0, 2000), rnd.next(0, 60));
        second = intervalNear(LIMIT - rnd.next(0, 2000), rnd.next(0, 60));
    } else if (mode == 4) {
        int base = rnd.next(1, LIMIT - 200);
        first = intervalNear(base, rnd.next(0, 80));
        second = intervalNear(base + rnd.next(0, 200), rnd.next(0, 80));
    } else {
        first = intervalWithWidth(1, LIMIT, rnd.next(0, 1000));
        second = intervalWithWidth(1, LIMIT, rnd.next(0, 1000));
    }

    println(first.first, first.second, second.first, second.second);
    return 0;
}
