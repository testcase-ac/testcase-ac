#include "testlib.h"

#include <algorithm>
#include <array>
#include <utility>
#include <vector>

using namespace std;

const long long MIN_COORD = -1000000000LL;
const long long MAX_COORD = 1000000000LL;

long long randomCoord() {
    return rnd.next(MIN_COORD, MAX_COORD);
}

long long randomSmallCoord() {
    return rnd.next(-20LL, 20LL);
}

long long differentFrom(long long value) {
    long long result = randomSmallCoord();
    while (result == value) {
        result = randomSmallCoord();
    }
    return result;
}

long long outsideSegment(long long a, long long b) {
    long long lo = min(a, b);
    long long hi = max(a, b);
    vector<long long> candidates;
    for (long long value = -25; value <= 25; ++value) {
        if (value < lo || value > hi) {
            candidates.push_back(value);
        }
    }
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    using Point = pair<long long, long long>;

    Point s, e, p;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        s = {randomSmallCoord(), randomSmallCoord()};
        e = {differentFrom(s.first), differentFrom(s.second)};
        p = {rnd.next(0, 1) ? s.first : e.first, differentFrom(s.second)};
        if (p == e) {
            p.second = differentFrom(e.second);
        }
    } else if (mode == 1) {
        long long y = randomSmallCoord();
        long long x1 = rnd.next(-20LL, 15LL);
        long long x2 = rnd.next(x1 + 1, 20LL);
        s = {x1, y};
        e = {x2, y};
        p = {outsideSegment(x1, x2), rnd.next(0, 1) ? y : differentFrom(y)};
    } else if (mode == 2) {
        long long y = randomSmallCoord();
        long long x1 = rnd.next(-20LL, 15LL);
        long long x2 = rnd.next(x1 + 1, 20LL);
        long long px = rnd.next(x1, x2);
        s = {x1, y};
        e = {x2, y};
        p = {px, y};
        if (rnd.next(0, 1)) {
            swap(s, e);
        }
    } else if (mode == 3) {
        long long x = randomSmallCoord();
        long long y1 = rnd.next(-20LL, 15LL);
        long long y2 = rnd.next(y1 + 1, 20LL);
        s = {x, y1};
        e = {x, y2};
        p = {rnd.next(0, 1) ? x : differentFrom(x), outsideSegment(y1, y2)};
    } else if (mode == 4) {
        long long x = randomSmallCoord();
        long long y1 = rnd.next(-20LL, 15LL);
        long long y2 = rnd.next(y1 + 1, 20LL);
        long long py = rnd.next(y1, y2);
        s = {x, y1};
        e = {x, y2};
        p = {x, py};
        if (rnd.next(0, 1)) {
            swap(s, e);
        }
    } else if (mode == 5) {
        array<long long, 4> xs = {MIN_COORD, MAX_COORD, randomSmallCoord(), -randomSmallCoord()};
        array<long long, 4> ys = {MIN_COORD, MAX_COORD, randomSmallCoord(), -randomSmallCoord()};
        shuffle(xs.begin(), xs.end());
        shuffle(ys.begin(), ys.end());
        s = {xs[0], ys[0]};
        e = {xs[1], ys[1]};
        p = {xs[2], ys[2]};
    } else {
        s = {randomCoord(), randomCoord()};
        e = {randomCoord(), randomCoord()};
        p = {randomCoord(), randomCoord()};
    }

    while (s == e) {
        e = {randomCoord(), randomCoord()};
    }
    while (s == p || e == p) {
        p = {randomCoord(), randomCoord()};
    }

    println(s.first, s.second);
    println(e.first, e.second);
    println(p.first, p.second);

    return 0;
}
