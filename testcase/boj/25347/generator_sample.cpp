#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static long long randomValue(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(1, 1000);
    if (mode == 2) return rnd.next(999999900, 1000000000);
    return rnd.any(vector<long long>{1, 2, 3, 10, 1000, 1000000000});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 5 ? rnd.next(30, 60) : rnd.next(1, 12);

    int x = 1;
    int y = 1;
    if (mode == 0) {
        y = rnd.next(1, 20);
        x = rnd.next(1, y);
    } else if (mode == 1) {
        y = 1000000000;
        x = rnd.next(1, 1000);
    } else if (mode == 2) {
        y = 1000000000;
        x = rnd.next(999999000, y);
    } else if (mode == 3) {
        y = rnd.next(2, 1000000000);
        x = y;
    } else {
        y = rnd.next(1, 1000000000);
        x = rnd.next(1, y);
    }

    vector<long long> r(n), b(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            r[i] = b[i] = randomValue(0);
        } else if (mode == 1) {
            r[i] = rnd.next(1, 10);
            b[i] = randomValue(rnd.next(0, 3));
        } else if (mode == 2) {
            r[i] = randomValue(rnd.next(0, 3));
            b[i] = rnd.next(1, 10);
        } else if (mode == 3) {
            r[i] = randomValue(i % 4);
            b[i] = randomValue((i + 2) % 4);
        } else if (mode == 4) {
            long long base = rnd.next(1, 1000000);
            r[i] = base;
            b[i] = rnd.next(1, 4) == 1 ? base : rnd.next(1, 1000000);
        } else {
            r[i] = rnd.next(1, 1000000000);
            b[i] = rnd.next(1, 1000000000);
        }
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    vector<long long> rr(n), bb(n);
    for (int i = 0; i < n; ++i) {
        rr[i] = r[order[i]];
        bb[i] = b[order[i]];
    }

    println(n, x, y);
    println(rr);
    println(bb);

    return 0;
}
