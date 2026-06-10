#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

long long minNines(int h) {
    return 1LL * h * (h - 1) / 2;
}

long long maxNines(int h, int w) {
    return 1LL * h * (2 * w - h + 1) / 2;
}

pair<int, int> randomShape(int maxCells) {
    int h = rnd.next(1, maxCells);
    int w = rnd.next(1, maxCells / h);
    if (rnd.next(2)) swap(h, w);
    return {h, w};
}

pair<int, int> solvableShape(int maxCells) {
    int maxH = 1;
    while (1LL * (maxH + 1) * max(1, maxH) <= maxCells) ++maxH;

    int h = rnd.next(1, min(80, maxH));
    int w = rnd.next(max(1, h - 1), maxCells / h);
    if (rnd.next(4) == 0) {
        h = rnd.next(1, maxH);
        w = rnd.next(max(1, h - 1), 100000 / h);
    }
    return {h, w};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int h = 1, w = 1;
    long long d = 0;
    int mode = rnd.next(8);

    if (mode == 0) {
        h = rnd.next(1, 8);
        w = rnd.next(1, 8);
        d = rnd.next(0, h * w);
    } else if (mode == 1) {
        tie(h, w) = solvableShape(100000);
        long long lo = minNines(h);
        long long hi = maxNines(h, w);
        d = rnd.next(lo, hi);
    } else if (mode == 2) {
        tie(h, w) = solvableShape(100000);
        vector<long long> choices = {minNines(h), maxNines(h, w)};
        d = rnd.any(choices);
    } else if (mode == 3) {
        tie(h, w) = solvableShape(100000);
        long long lo = minNines(h);
        long long hi = maxNines(h, w);
        vector<long long> choices;
        choices.push_back(max(0LL, lo - 1));
        if (hi + 1 <= 1LL * h * w) choices.push_back(hi + 1);
        d = rnd.any(choices);
    } else if (mode == 4) {
        int maxH = 1;
        while (1LL * (maxH + 1) * maxH <= 100000) ++maxH;
        h = rnd.next(2, maxH);
        w = rnd.next(1, h - 1);
        d = rnd.next(0, h * w);
    } else if (mode == 5) {
        h = rnd.next(1, 100000);
        w = 1;
        d = rnd.next(0, h);
    } else if (mode == 6) {
        h = 1;
        w = rnd.next(1, 100000);
        d = rnd.next(0, w);
    } else {
        tie(h, w) = randomShape(100000);
        if (rnd.next(2) && h > w + 1) swap(h, w);
        d = rnd.next(0, h * w);
    }

    int c = h * w - d;
    println(h, w);
    println(c, (int)d);

    return 0;
}
