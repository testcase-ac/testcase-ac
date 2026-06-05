#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 5) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(6, 30);
    }

    int c;
    if (mode == 1) {
        c = 1;
    } else if (mode == 2) {
        c = n;
    } else {
        c = rnd.next(1, n);
    }

    int minM = (n + c - 1) / c;
    int m;
    if (mode == 3) {
        m = minM;
    } else {
        m = rnd.next(minM, n);
    }

    vector<int> times;
    times.reserve(n);

    if (mode == 0) {
        int value = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            times.push_back(value);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            times.push_back(rnd.next(0, 40));
        }
    } else if (mode == 2) {
        int base = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            int offset = (i % 3 == 0) ? 0 : rnd.next(0, 4);
            times.push_back(base + i / 3 * rnd.next(1, 5) + offset);
        }
    } else if (mode == 3) {
        int current = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && i % c == 0) {
                current += rnd.next(20, 200);
            } else {
                current += rnd.next(0, 5);
            }
            times.push_back(current);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                times.push_back(rnd.next(999999990, 1000000000));
            } else {
                times.push_back(rnd.next(0, 20));
            }
        }
    } else {
        int step = rnd.next(1, 1000000000 / max(1, n));
        int start = rnd.next(0, 1000000000 - step * (n - 1));
        for (int i = 0; i < n; ++i) {
            times.push_back(start + step * i);
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(times.begin(), times.end());
    }

    println(n, m, c);
    println(times);
    return 0;
}
