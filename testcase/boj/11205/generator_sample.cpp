#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

const int COORD_LIMIT = 100000000;

int differentCoord(int from, int low, int high) {
    int to = rnd.next(low, high);
    if (to == from) {
        if (to < high) {
            ++to;
        } else {
            --to;
        }
    }
    return to;
}

int boundedCoord(long long value) {
    return static_cast<int>(max<long long>(-COORD_LIMIT, min<long long>(COORD_LIMIT, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int m = 0, l = 0, M = 1, L = -1;
    int tm = 1, tl = 1;

    if (mode == 0) {
        int span = rnd.next(2, 12);
        m = rnd.next(-span, span);
        l = rnd.next(-span, span);
        M = differentCoord(m, -span, span);
        L = differentCoord(l, -span, span);
        tm = rnd.next(1, 2 * span + 8);
        tl = rnd.next(1, 2 * span + 8);
    } else if (mode == 1) {
        int a = rnd.next(1, 20);
        int b = rnd.next(1, 20);
        m = -a;
        l = b;
        M = rnd.next(0, 1) ? a : a + rnd.next(1, 5);
        L = rnd.next(0, 1) ? -b : -b - rnd.next(1, 5);
        tm = rnd.next(1, a + b + 8);
        tl = rnd.next(1, a + b + 8);
    } else if (mode == 2) {
        m = rnd.next(-15, 15);
        l = rnd.next(-15, 15);
        M = differentCoord(m, -15, 15);
        L = differentCoord(l, -15, 15);
        tm = abs(m) + abs(M - m) + rnd.next(0, 5);
        tl = abs(l) + abs(L - l) + rnd.next(0, 5);
    } else if (mode == 3) {
        int base = rnd.next(-10, 10);
        m = base;
        l = base;
        M = differentCoord(m, -20, 20);
        L = differentCoord(l, -20, 20);
        tm = rnd.next(1, 45);
        tl = rnd.next(1, 45);
    } else if (mode == 4) {
        int target = rnd.next(-10, 10);
        M = target;
        L = target;
        m = differentCoord(M, -20, 20);
        l = differentCoord(L, -20, 20);
        tm = rnd.next(1, 45);
        tl = rnd.next(1, 45);
    } else if (mode == 5) {
        int edge = rnd.next(0, 1) ? COORD_LIMIT : -COORD_LIMIT;
        m = edge;
        M = -edge;
        l = rnd.next(-100, 100);
        L = differentCoord(l, -100, 100);
        tm = rnd.next(1, COORD_LIMIT);
        tl = rnd.next(1, 1000);
    } else {
        int span = rnd.next(1, 30);
        m = rnd.next(-span, span);
        l = rnd.next(-span, span);
        M = differentCoord(m, -span, span);
        L = differentCoord(l, -span, span);
        int directM = abs(m) + abs(M - m);
        int directL = abs(l) + abs(L - l);
        tm = rnd.next(max(1, directM - 2), directM + 2);
        tl = rnd.next(max(1, directL - 2), directL + 2);
    }

    if (rnd.next(0, 9) == 0) {
        int delta = rnd.next(-5, 5);
        m = boundedCoord(static_cast<long long>(m) + delta);
        l = boundedCoord(static_cast<long long>(l) + delta);
        M = boundedCoord(static_cast<long long>(M) + delta);
        L = boundedCoord(static_cast<long long>(L) + delta);
    }

    if (m == M) {
        M = differentCoord(m, -COORD_LIMIT, COORD_LIMIT);
    }
    if (l == L) {
        L = differentCoord(l, -COORD_LIMIT, COORD_LIMIT);
    }

    tm = max(1, min(tm, COORD_LIMIT));
    tl = max(1, min(tl, COORD_LIMIT));

    println(m, l);
    println(M, L);
    println(tm, tl);

    return 0;
}
