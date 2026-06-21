#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Rect {
    int a, b, c, d;
};

static Rect makeRect(int n, int m, int mode) {
    if (mode == 0) {
        int r = rnd.next(1, n);
        int c = rnd.next(1, m);
        return {r, c, r, c};
    }
    if (mode == 1) {
        int a = rnd.next(1, n);
        int c = rnd.next(a, n);
        return {a, 1, c, m};
    }
    if (mode == 2) {
        int b = rnd.next(1, m);
        int d = rnd.next(b, m);
        return {1, b, n, d};
    }
    if (mode == 3) {
        return {1, 1, n, m};
    }

    int a = rnd.next(1, n);
    int b = rnd.next(1, m);
    int maxHeight = rnd.next(1, max(1, min(n - a + 1, 8)));
    int maxWidth = rnd.next(1, max(1, min(m - b + 1, 8)));
    return {a, b, a + maxHeight - 1, b + maxWidth - 1};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 5);
    int n, m;
    if (shape == 0) {
        n = 1;
        m = rnd.next(1, 10);
    } else if (shape == 1) {
        n = rnd.next(1, 10);
        m = 1;
    } else if (shape == 2) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
    } else if (shape == 3) {
        n = rnd.next(7, 20);
        m = rnd.next(2, 10);
    } else if (shape == 4) {
        n = rnd.next(2, 10);
        m = rnd.next(7, 20);
    } else {
        n = rnd.next(8, 25);
        m = rnd.next(8, 25);
    }

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = rnd.next(2, 8);
    } else if (kMode == 2) {
        k = rnd.next(9, 25);
    } else {
        k = rnd.next(26, 60);
    }

    vector<Rect> rects;
    rects.reserve(k);
    for (int i = 0; i < k; ++i) {
        if (!rects.empty() && rnd.next(0, 99) < 20) {
            rects.push_back(rnd.any(rects));
            continue;
        }

        int mode = rnd.next(0, 4);
        if (i == 0 && rnd.next(0, 3) == 0) mode = 3;
        rects.push_back(makeRect(n, m, mode));
    }

    println(n, m);
    println(k);
    for (const Rect& r : rects) {
        println(r.a, r.b, r.c, r.d);
    }

    return 0;
}
