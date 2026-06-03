#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedValue(long long x) {
    if (x < -100000000LL) return -100000000;
    if (x > 100000000LL) return 100000000;
    return static_cast<int>(x);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 3;
    vector<int> a;

    if (mode == 0) {
        n = 3;
        a = {-100000000, 0, 100000000};
        int tweak = rnd.next(-20, 20);
        int index = rnd.next(0, 2);
        a[index] = boundedValue(a[index] + tweak);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        int base = rnd.next(-100000000, 100000000);
        int other = rnd.next(-100000000, 100000000);
        int rare = rnd.next(-100000000, 100000000);
        for (int i = 0; i < n; ++i) {
            if (i < n - 2) {
                a.push_back(base);
            } else if (i == n - 2) {
                a.push_back(other);
            } else {
                a.push_back(rare);
            }
        }
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        int start = rnd.next(-1000, 1000);
        int step = rnd.next(1, 200000000 / max(1, n - 1));
        if (rnd.next(0, 1)) step = -step;
        for (int i = 0; i < n; ++i) {
            a.push_back(boundedValue(start + 1LL * i * step));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        int center = rnd.next(-1000000, 1000000);
        int radius = rnd.next(0, 200);
        for (int i = 0; i < n; ++i) {
            a.push_back(boundedValue(center + rnd.next(-radius, radius)));
        }
    } else if (mode == 4) {
        n = rnd.next(6, 30);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                a.push_back(rnd.next(-100000000, -99990000));
            } else if (bucket == 1) {
                a.push_back(rnd.next(-1000, 1000));
            } else if (bucket == 2) {
                a.push_back(rnd.next(99990000, 100000000));
            } else {
                a.push_back(rnd.next(-100000000, 100000000));
            }
        }
    } else {
        n = rnd.next(3, 40);
        int lo = rnd.next(-100000000, 100000000);
        int hi = rnd.next(lo, 100000000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    for (int x : a) {
        println(x);
    }

    return 0;
}
