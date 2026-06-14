#include "testlib.h"
#include <algorithm>

using namespace std;

const long long LIMIT = 1000000000LL;

long long boundedStart(long long delta) {
    return rnd.next(0LL, LIMIT - delta);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 50);
    long long sx = 0;
    long long sy = 0;
    long long mx = 0;
    long long my = 0;

    if (mode == 0) {
        sx = rnd.next(0LL, LIMIT);
        sy = rnd.next(0LL, LIMIT);
        mx = sx;
        my = sy;
    } else if (mode == 1) {
        long long dx = rnd.next(1LL, 200LL);
        sx = boundedStart(dx);
        sy = rnd.next(0LL, LIMIT);
        mx = sx + dx;
        my = sy;
    } else if (mode == 2) {
        long long dy = rnd.next(1LL, 200LL);
        sx = rnd.next(0LL, LIMIT);
        sy = boundedStart(dy);
        mx = sx;
        my = sy + dy;
    } else if (mode == 3) {
        sx = rnd.next(1LL, LIMIT);
        sy = rnd.next(0LL, LIMIT);
        mx = rnd.next(0LL, sx - 1);
        my = rnd.next(0LL, LIMIT);
    } else if (mode == 4) {
        sx = rnd.next(0LL, LIMIT);
        sy = rnd.next(1LL, LIMIT);
        mx = rnd.next(0LL, LIMIT);
        my = rnd.next(0LL, sy - 1);
    } else if (mode == 5) {
        n = rnd.next(2, 50);
        int r = rnd.next(1, n - 1);
        int u = n - r;
        long long cycles = rnd.next(2LL, 20000000LL);
        long long step = max((long long)r, (long long)u) * cycles;
        sx = boundedStart(step);
        sy = boundedStart(step);
        mx = sx + r * cycles + rnd.next(0, r);
        my = sy + u * cycles + rnd.next(0, u);
    } else if (mode == 6) {
        n = rnd.next(45, 50);
        sx = rnd.next(max(0LL, LIMIT - 1000), LIMIT);
        sy = rnd.next(max(0LL, LIMIT - 1000), LIMIT);
        mx = rnd.next(sx, LIMIT);
        my = rnd.next(sy, LIMIT);
    } else {
        long long dx = rnd.next(0LL, 500LL);
        long long dy = rnd.next(0LL, 500LL);
        sx = boundedStart(dx);
        sy = boundedStart(dy);
        mx = sx + dx;
        my = sy + dy;
    }

    println(n, sx, sy, mx, my);
    return 0;
}
