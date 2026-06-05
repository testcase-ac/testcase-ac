#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedValue(int lo, int hi) {
    return rnd.next(max(0, lo), min(100, hi));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 20);
    int k = rnd.next(1, 100);
    vector<int> a(n);

    if (mode == 0) {
        k = rnd.next(40, 100);
        int cap = rnd.next(0, min(20, k - 1));
        for (int& x : a) {
            x = boundedValue(0, cap);
        }
    } else if (mode == 1) {
        k = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int remaining = n - i;
            if (remaining >= 2 && rnd.next(3) == 0) {
                int first = rnd.next(0, k);
                a[i] = first;
                a[++i] = k - first;
            } else {
                a[i] = boundedValue(0, k + 3);
            }
        }
    } else if (mode == 2) {
        k = rnd.next(1, 60);
        for (int& x : a) {
            if (rnd.next(4) == 0) {
                x = rnd.next(k, 100);
            } else {
                x = boundedValue(0, k - 1);
            }
        }
    } else if (mode == 3) {
        k = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? rnd.next(0, 3) : rnd.next(80, 100);
        }
        if (rnd.next(2) == 0) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 4) {
        k = rnd.next(5, 80);
        int lo = rnd.next(0, min(10, k));
        int hi = rnd.next(max(lo, k - 5), min(100, k + 20));
        for (int& x : a) {
            x = rnd.next(lo, hi);
        }
    } else {
        k = rnd.next(1, 100);
        for (int& x : a) {
            x = rnd.next(0, 100);
        }
    }

    println(n, k);
    println(a);

    return 0;
}
