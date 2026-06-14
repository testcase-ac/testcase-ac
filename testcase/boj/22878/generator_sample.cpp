#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MIN_A = 1;
const int MAX_A = 1000000;

int clipped(int x) {
    return max(MIN_A, min(MAX_A, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    vector<int> p(n), q(n);

    if (mode == 0) {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, lo + rnd.next(0, 20));
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(lo, hi);
            q[i] = rnd.next(lo, hi);
        }
    } else if (mode == 1) {
        vector<int> vals = {1, 2, 999999, 1000000};
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.any(vals);
            q[i] = rnd.any(vals);
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 1000000);
        int drift = rnd.next(-5, 5);
        for (int i = 0; i < n; ++i) {
            p[i] = clipped(base + rnd.next(-3, 3));
            q[i] = clipped(p[i] + drift + rnd.next(-2, 2));
        }
    } else if (mode == 3) {
        int lo = rnd.next(1, 999900);
        int step = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            p[i] = clipped(lo + i * step);
            q[i] = clipped(lo + (n - 1 - i) * step);
        }
        shuffle(p.begin(), p.end());
        shuffle(q.begin(), q.end());
    } else if (mode == 4) {
        int a = rnd.next(1, 1000000);
        int b = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            p[i] = (rnd.next(0, 4) == 0 ? rnd.next(1, 1000000) : a);
            q[i] = (rnd.next(0, 4) == 0 ? rnd.next(1, 1000000) : b);
        }
    } else if (mode == 5) {
        int center = rnd.next(50, 999950);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-40, 40);
            p[i] = clipped(center + delta);
            q[i] = clipped(center - delta + rnd.next(-3, 3));
        }
    } else {
        n = rnd.next(20, 60);
        p.resize(n);
        q.resize(n);
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(1, 1000000);
            q[i] = rnd.next(1, 1000000);
        }
    }

    println(n);
    println(p);
    println(q);
    return 0;
}
