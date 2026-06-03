#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampDamage(int x) {
    return max(1, min(100, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int h;
    int d;
    int k;
    vector<int> r;

    if (mode == 0) {
        n = rnd.next(1, 3);
        h = rnd.next(1, 20);
        d = rnd.next(1, 10);
        k = rnd.next(1, 3);
        int base = rnd.next(1, 15);
        for (int i = 0; i < n; ++i) {
            r.push_back(clampDamage(base + rnd.next(-3, 8)));
        }
    } else if (mode == 1) {
        n = rnd.next(12, 18);
        h = rnd.next(1, 80);
        d = rnd.next(1, 4);
        k = rnd.next(1, 2);
        for (int i = 0; i < n; ++i) {
            r.push_back(rnd.next(70, 100));
        }
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        h = rnd.next(200, 1000);
        d = rnd.next(1, 5);
        k = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            int expectedDistance = d + i * k;
            r.push_back(clampDamage(expectedDistance + rnd.next(-2, 6)));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        h = rnd.next(20, 250);
        d = rnd.next(1, 10);
        k = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                r.push_back(rnd.next(1, d));
            } else {
                r.push_back(rnd.next(60, 100));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 18);
        h = rnd.next(1, 1000);
        d = rnd.next(1, 10);
        k = rnd.next(1, 3);
        int pivot = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(1, 30);
            if (i == pivot || (i + 1 == pivot && rnd.next(0, 1))) {
                value = rnd.next(80, 100);
            }
            r.push_back(value);
        }
    } else if (mode == 5) {
        n = 18;
        h = rnd.next(900, 1000);
        d = rnd.next(8, 10);
        k = 3;
        int low = rnd.next(1, 20);
        int high = rnd.next(40, 100);
        for (int i = 0; i < n; ++i) {
            r.push_back(i % 3 == 0 ? high : rnd.next(low, min(100, low + 25)));
        }
    } else {
        n = rnd.next(1, 18);
        h = rnd.next(1, 1000);
        d = rnd.next(1, 10);
        k = rnd.next(1, 3);
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i) {
            r.push_back(rnd.next(lo, hi));
        }
    }

    println(n);
    println(h, d, k);
    for (int value : r) {
        println(value);
    }

    return 0;
}
