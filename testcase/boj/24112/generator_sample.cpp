#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    int p = 0;
    vector<int> h;

    if (mode == 0) {
        n = rnd.next(2, 12);
        p = rnd.next(1, 20);
        h.resize(n);
        for (int& x : h) x = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(3, 16);
        int unit = rnd.next(1, 9);
        int maxJump = rnd.next(1, min(n, 6));
        p = unit * maxJump;
        h.assign(n, unit);
    } else if (mode == 2) {
        n = rnd.next(4, 14);
        p = rnd.next(15, 80);
        h.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) h[i] = rnd.next(max(1, p - 5), p + 5);
            else h[i] = rnd.next(1, max(1, p / 3));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 18);
        h.resize(n);
        int total = 0;
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(1, 25);
            total += h[i];
        }
        p = rnd.next(max(1, total / 2), total);
    } else if (mode == 4) {
        n = rnd.next(6, 20);
        p = rnd.next(10, 60);
        h.resize(n);
        for (int i = 0; i < n; ++i) {
            int remaining = max(1, p - (i % 4));
            h[i] = rnd.next(max(1, remaining / 2), remaining);
        }
    } else {
        n = rnd.next(10, 30);
        p = rnd.next(100000000, 500000000);
        h.resize(n);
        long long remaining = 500000000LL;
        for (int i = 0; i < n; ++i) {
            int slotsLeft = n - i;
            int upper = (int)min<long long>(500000000, remaining - (slotsLeft - 1));
            h[i] = rnd.next(1, min(upper, 50000000));
            remaining -= h[i];
        }
    }

    if (rnd.next(0, 1)) shuffle(h.begin(), h.end());

    println(n, p);
    for (int x : h) println(x);
    return 0;
}
