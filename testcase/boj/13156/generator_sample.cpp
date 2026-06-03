#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int c = rnd.next(1, 14);
    int m = rnd.next(1, 12);

    if (mode == 1) {
        c = rnd.next(1, 6);
        m = rnd.next(1, 5);
    } else if (mode == 6) {
        c = rnd.next(12, 25);
        m = rnd.next(8, 18);
    } else if (mode == 7) {
        c = rnd.next(1, 100);
        m = rnd.next(1, 4);
    }

    vector<vector<int>> price(m, vector<int>(c));

    for (int merchant = 0; merchant < m; ++merchant) {
        if (mode == 0) {
            int lo = rnd.next(1, 30);
            int hi = rnd.next(lo, 200);
            for (int cpus = 0; cpus < c; ++cpus) {
                price[merchant][cpus] = rnd.next(lo, hi);
            }
        } else if (mode == 1) {
            for (int cpus = 0; cpus < c; ++cpus) {
                price[merchant][cpus] = 1;
            }
            price[merchant][rnd.next(c)] = rnd.next(50000, 100000);
        } else if (mode == 2) {
            int unit = rnd.next(1, 40);
            int bonusAt = rnd.next(1, c);
            for (int cpus = 1; cpus <= c; ++cpus) {
                int value = unit * cpus + rnd.next(0, 20);
                if (cpus == bonusAt) value += rnd.next(100, 500);
                price[merchant][cpus - 1] = min(value, 100000);
            }
        } else if (mode == 3) {
            int favored = (merchant % c) + 1;
            for (int cpus = 1; cpus <= c; ++cpus) {
                int value = rnd.next(1, 30);
                if (cpus == favored) value = rnd.next(1000, 5000);
                price[merchant][cpus - 1] = value;
            }
        } else if (mode == 4) {
            int current = rnd.next(1, 20);
            for (int cpus = 0; cpus < c; ++cpus) {
                current += rnd.next(0, 120);
                price[merchant][cpus] = min(current, 100000);
            }
        } else if (mode == 5) {
            int high = rnd.next(90000, 100000);
            for (int cpus = 0; cpus < c; ++cpus) {
                price[merchant][cpus] = rnd.next(max(1, high - 1000), high);
            }
        } else {
            int plateau = rnd.next(1, 1000);
            for (int cpus = 0; cpus < c; ++cpus) {
                price[merchant][cpus] = plateau + rnd.next(0, 10);
            }
            if (rnd.next(0, 1)) {
                reverse(price[merchant].begin(), price[merchant].end());
            }
        }
    }

    println(c, m);
    for (const auto& row : price) {
        println(row);
    }

    return 0;
}
