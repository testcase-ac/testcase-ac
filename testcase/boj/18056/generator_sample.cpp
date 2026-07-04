#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(20, 80);
    } else {
        n = rnd.next(2, 12);
    }

    int c = rnd.next(1, n);
    int y;
    if (mode == 0) {
        y = n - 1;
    } else if (mode == 4) {
        y = rnd.next(max(n - 1, 999999900), 1000000000);
    } else {
        y = rnd.next(n - 1, min(1000, 1000000000));
    }

    vector<int> x(n);
    int base = n - 1;
    int mod = y + 1;

    if (mode <= 2) {
        int residue = rnd.next(0, min(mod - 1, 30));
        int minValue = base;
        while (minValue % mod != residue) {
            ++minValue;
        }
        for (int i = 0; i < n; ++i) {
            int steps = rnd.next(0, 8);
            x[i] = minValue + steps * mod;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(base, min(base + 80, 1000000000));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(max(base, 999999850), 1000000000);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int span = rnd.next(0, 2000);
            x[i] = base + span;
        }
        shuffle(x.begin(), x.end());
    }

    if (mode == 1) {
        x[c - 1] = rnd.next(base, min(base + 200, 1000000000));
    }
    if (mode == 2 && n > 2) {
        int different = rnd.next(1, n);
        while (different == c) {
            different = rnd.next(1, n);
        }
        x[different - 1] = min(1000000000, x[different - 1] + rnd.next(1, min(20, mod)));
    }

    println(n, c, y);
    println(x);
    return 0;
}
