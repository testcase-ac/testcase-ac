#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 25);
    int q = rnd.next(1, 35);
    if (mode == 6) {
        n = rnd.next(40, 120);
        q = rnd.next(60, 160);
    }

    vector<int> special = {
        1, 2, 3, 4, 5, 6, 12, 24, 36, 60, 72, 120, 180, 240,
        360, 720, 840, 1260, 2520, 5040, 7560, 10080, 83160,
        720720, 831600, 997920, 1000000
    };

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            a[i] = rnd.next(1, 2);
        } else if (mode == 1) {
            a[i] = rnd.any(special);
        } else if (mode == 2) {
            a[i] = rnd.next(1, 40);
        } else if (mode == 3) {
            a[i] = (i % 3 == 0 ? 1000000 : rnd.any(special));
        } else if (mode == 4) {
            int base = rnd.next(2, 20);
            int exponent = rnd.next(1, 5);
            int value = 1;
            for (int j = 0; j < exponent && value <= 1000000 / base; ++j) {
                value *= base;
            }
            a[i] = value;
        } else {
            a[i] = rnd.next(1, 1000000);
        }
    }

    println(n, q);
    println(a);

    for (int i = 0; i < q; ++i) {
        int t;
        if (mode == 0) {
            t = 1;
        } else if (mode == 5) {
            t = 2;
        } else if (i % 5 == 0) {
            t = 2;
        } else {
            t = rnd.next(1, 2);
        }

        int s, e;
        int rangeMode = rnd.next(0, 5);
        if (rangeMode == 0) {
            s = 1;
            e = n;
        } else if (rangeMode == 1) {
            s = e = rnd.next(1, n);
        } else if (rangeMode == 2) {
            s = 1;
            e = rnd.next(1, n);
        } else if (rangeMode == 3) {
            s = rnd.next(1, n);
            e = n;
        } else {
            s = rnd.next(1, n);
            e = rnd.next(s, n);
        }

        println(t, s, e);
    }

    return 0;
}
