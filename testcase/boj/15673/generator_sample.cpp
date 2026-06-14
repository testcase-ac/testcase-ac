#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedValue(int lo, int hi) {
    return rnd.next(max(lo, -100), min(hi, 100));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(2, 40);
    if (mode == 0) n = rnd.next(2, 6);
    if (mode == 7) n = rnd.next(41, 120);

    vector<int> p(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.any(vector<int>{-100, -1, 0, 1, 100});
        }
    } else if (mode == 1) {
        int hi = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(1, hi);
        }
    } else if (mode == 2) {
        int lo = rnd.next(-100, -1);
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(lo, -1);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                p[i] = rnd.next(-100, 100);
            } else {
                p[i] = 0;
            }
        }
    } else if (mode == 4) {
        int magnitude = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int noise = rnd.next(0, min(5, magnitude - 1));
            p[i] = (i % 2 == 0 ? magnitude - noise : -magnitude + noise);
        }
    } else if (mode == 5) {
        int split1 = rnd.next(1, n - 1);
        int split2 = rnd.next(split1, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i < split1) {
                p[i] = boundedValue(20, 100);
            } else if (i < split2) {
                p[i] = boundedValue(-15, 15);
            } else {
                p[i] = boundedValue(-100, -20);
            }
        }
    } else if (mode == 6) {
        int lo = rnd.next(-100, 0);
        int hi = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(lo, hi);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 9) == 0) {
                p[i] = rnd.any(vector<int>{-100, 100});
            } else {
                p[i] = rnd.next(-12, 12);
            }
        }
    }

    println(n);
    println(p);

    return 0;
}
