#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long MOD = 1000000007LL;
const long long MAX_VALUE = 1000000000LL;

long long valueForMode(int mode) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return rnd.next(MOD - 30, MAX_VALUE);
    if (mode == 2) return rnd.next(MAX_VALUE - 30, MAX_VALUE);
    return rnd.next(1LL, MAX_VALUE);
}

pair<int, int> rangeForMode(int n, int mode) {
    if (mode == 0) return {1, n};
    if (mode == 1) {
        int y = rnd.next(1, n);
        return {1, y};
    }
    if (mode == 2) {
        int x = rnd.next(1, n);
        return {x, n};
    }
    if (mode == 3) {
        int x = rnd.next(1, n);
        return {x, x};
    }

    int x = rnd.next(1, n);
    int y = rnd.next(1, n);
    if (x > y) swap(x, y);
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 5);
    int n;
    if (shape == 0) {
        n = 1;
    } else if (shape == 1) {
        n = rnd.next(2, 4);
    } else if (shape == 2) {
        n = rnd.next(5, 9);
    } else {
        n = rnd.next(10, 18);
    }

    int m = rnd.next(max(4, n), max(8, 3 * n));

    vector<long long> a(n);
    int initialMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        a[i] = valueForMode((initialMode + rnd.next(0, 3)) % 4);
    }

    println(n);
    println(a);
    println(m);

    for (int i = 0; i < m; ++i) {
        int type;
        if (i == 0 || i == m - 1) {
            type = 4;
        } else {
            int mode = rnd.next(0, 99);
            if (mode < 25) type = 1;
            else if (mode < 50) type = 2;
            else if (mode < 75) type = 3;
            else type = 4;
        }

        auto [x, y] = rangeForMode(n, rnd.next(0, 4));
        if (type == 4) {
            println(type, x, y);
        } else {
            println(type, x, y, valueForMode(rnd.next(0, 3)));
        }
    }

    return 0;
}
