#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int pickPerimeter(int n, int m, int mode) {
    int maxP = 2 * (n + m);
    vector<int> candidates;

    auto add = [&](int p) {
        p = max(4, min(maxP, p));
        candidates.push_back(p);
    };

    add(4);
    add(6);
    add(maxP);
    add(maxP - 2);
    add((maxP + 4) / 2);
    add(2 * (n + 1));
    add(2 * (m + 1));

    if (mode % 3 == 0) {
        return rnd.any(candidates);
    }
    if (mode % 3 == 1) {
        int half = rnd.next(2, n + m);
        return 2 * half;
    }
    return rnd.next(4, maxP);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n, m;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(1, 100);
    } else if (mode == 2) {
        n = rnd.next(1, 100);
        m = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        m = rnd.next(30, 100);
    } else if (mode == 4) {
        n = rnd.next(30, 100);
        m = rnd.next(2, 10);
    } else if (mode == 5) {
        int base = rnd.next(6, 30);
        n = rnd.next(max(1, base - 3), min(100, base + 3));
        m = rnd.next(max(1, base - 3), min(100, base + 3));
    } else if (mode == 6) {
        n = rnd.next(80, 100);
        m = rnd.next(80, 100);
    } else {
        n = rnd.next(1, 100);
        m = rnd.next(1, 100);
    }

    if (rnd.next(0, 1)) {
        swap(n, m);
    }

    int p = pickPerimeter(n, m, mode);
    println(n, m, p);

    return 0;
}
