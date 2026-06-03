#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedSum(int x, int y, int z) {
    return max(-100000, min(100000, x + y + z));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 4);
        int lo = rnd.next(-5, 0);
        int hi = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 1) {
        n = rnd.next(5, 20);
        int base = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-3, 3);
            a.push_back(base + delta);
        }
    } else if (mode == 2) {
        n = rnd.next(6, 30);
        int step = rnd.next(1, 9);
        int cur = rnd.next(-40, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            cur += rnd.next(0, step);
        }
        if (rnd.next(2)) {
            for (int& x : a) {
                x = -x;
            }
        }
    } else if (mode == 3) {
        n = rnd.next(7, 35);
        int seedRange = rnd.next(3, 25);
        for (int i = 0; i < min(n, 3); ++i) {
            a.push_back(rnd.next(-seedRange, seedRange));
        }
        while ((int)a.size() < n) {
            if (rnd.next(100) < 70) {
                int x = rnd.any(a);
                int y = rnd.any(a);
                int z = rnd.any(a);
                a.push_back(boundedSum(x, y, z));
            } else {
                a.push_back(rnd.next(-seedRange * 3, seedRange * 3));
            }
        }
    } else {
        n = rnd.next(8, 40);
        vector<int> pool = {-100000, -99999, -50000, -1, 0, 1, 50000, 99999, 100000};
        for (int i = 0; i < n; ++i) {
            if (rnd.next(100) < 65) {
                a.push_back(rnd.any(pool));
            } else {
                a.push_back(rnd.next(-100000, 100000));
            }
        }
    }

    println(n);
    println(a);

    return 0;
}
