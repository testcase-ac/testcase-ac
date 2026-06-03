#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampTotal(int x) {
    return max(4, min(400, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 100);
    vector<int> stats(4);

    if (mode == 0) {
        int lo = rnd.next(1, 80);
        int hi = rnd.next(lo, min(100, lo + rnd.next(0, 20)));
        for (int& x : stats) {
            x = rnd.next(lo, hi);
        }
    } else if (mode == 1) {
        for (int& x : stats) {
            x = rnd.next(1, 100);
        }
        stats[rnd.next(0, 3)] = rnd.next(1, 5);
        stats[rnd.next(0, 3)] = rnd.next(90, 100);
    } else if (mode == 2) {
        n = rnd.next(20, 100);
        int target = rnd.next(4, 4 * n - 1);
        int remaining = target;
        for (int i = 0; i < 4; ++i) {
            int left = 3 - i;
            int lo = max(1, remaining - 100 * left);
            int hi = min(100, remaining - left);
            stats[i] = rnd.next(lo, hi);
            remaining -= stats[i];
        }
    } else if (mode == 3) {
        n = rnd.next(1, 80);
        int target = rnd.next(4 * n, 400);
        int remaining = target;
        for (int i = 0; i < 4; ++i) {
            int left = 3 - i;
            int lo = max(1, remaining - 100 * left);
            int hi = min(100, remaining - left);
            stats[i] = rnd.next(lo, hi);
            remaining -= stats[i];
        }
    } else {
        n = rnd.next(2, 99);
        int delta = rnd.next(-3, 3);
        int target = clampTotal(4 * n + delta);
        int remaining = target;
        for (int i = 0; i < 4; ++i) {
            int left = 3 - i;
            int lo = max(1, remaining - 100 * left);
            int hi = min(100, remaining - left);
            stats[i] = rnd.next(lo, hi);
            remaining -= stats[i];
        }
    }

    shuffle(stats.begin(), stats.end());
    println(stats[0], stats[1], stats[2], stats[3], n);
    return 0;
}
