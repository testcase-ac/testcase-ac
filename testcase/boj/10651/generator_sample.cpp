#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 3) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 28);
    }

    long long t;
    if (mode == 1) {
        t = 1;
    } else if (mode == 2) {
        t = rnd.next(2, 25);
    } else if (mode == 4) {
        t = rnd.next(100000000, 1000000000);
    } else {
        t = rnd.next(1, 1000000000);
    }

    vector<long long> positions(n), speeds(n);

    long long position = rnd.next(0, 8);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            long long gap;
            if (mode == 2) {
                gap = rnd.next(1, 3);
            } else if (mode == 4) {
                gap = rnd.next(1000000, 20000000);
            } else {
                gap = rnd.next(1, 20);
            }
            position = min(1000000000LL, position + gap);
        }
        positions[i] = position;
    }

    if (mode == 0) {
        speeds[0] = rnd.next(1, 1000000000);
    } else if (mode == 1) {
        long long base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            speeds[i] = base + rnd.next(0, 2);
        }
    } else if (mode == 2) {
        long long fast = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            speeds[i] = max(1LL, fast - i * rnd.next(1, 4) + rnd.next(0, 2));
        }
    } else if (mode == 3) {
        long long slow = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            speeds[i] = slow + i * rnd.next(1, 5);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            speeds[i] = rnd.next(1, 1000000000);
        }
    } else {
        long long base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            speeds[i] = base + (i % 3 == 0 ? rnd.next(0, 30) : rnd.next(0, 5));
        }
    }

    println(n, t);
    for (int i = 0; i < n; ++i) {
        println(positions[i], speeds[i]);
    }

    return 0;
}
