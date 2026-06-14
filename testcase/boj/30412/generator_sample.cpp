#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 1000000000;

int clampHeight(long long value) {
    return int(max(1LL, min<long long>(MAX_A, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(2, 30);
    int x;
    vector<int> a(n);

    if (mode == 0) {
        x = rnd.next(1, 12);
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a[i] = clampHeight(base + rnd.next(-x + 1, x - 1));
        }
    } else if (mode == 1) {
        x = rnd.next(1, 20);
        int base = rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            a[i] = clampHeight(base + 1LL * i * rnd.next(0, x + 2));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        a.assign(n, 0);
        x = rnd.next(1, 25);
        int center = rnd.next(1, n - 2);
        int high = rnd.next(x + 1, 80);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 80);
        }
        a[center] = rnd.next(1, max(1, high - x));
        a[center - 1] = high + rnd.next(0, x);
        a[center + 1] = high + rnd.next(0, x);
    } else if (mode == 3) {
        n = rnd.next(3, 30);
        a.assign(n, 0);
        x = rnd.next(1, 25);
        int center = rnd.next(1, n - 2);
        int low = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 80);
        }
        a[center] = low + x + rnd.next(0, 25);
        a[center - 1] = low + rnd.next(0, x - 1);
        a[center + 1] = low + rnd.next(0, x - 1);
    } else if (mode == 4) {
        x = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            int type = rnd.next(0, 2);
            if (type == 0) {
                a[i] = 1;
            } else if (type == 1) {
                a[i] = MAX_A;
            } else {
                a[i] = rnd.next(1, MAX_A);
            }
        }
    } else if (mode == 5) {
        n = rnd.next(2, 6);
        a.assign(n, 0);
        x = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, MAX_A);
        }
    } else if (mode == 6) {
        x = rnd.next(1, 30);
        int base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int delta = (i % 2 == 0 ? x : -x) + rnd.next(-1, 1);
            a[i] = clampHeight(base + 1LL * (i + 1) * delta);
        }
    } else {
        x = rnd.next(1, 40);
        int base = rnd.next(1, 120);
        for (int i = 0; i < n; ++i) {
            a[i] = clampHeight(base + 1LL * i * (x - 1) + rnd.next(0, 2));
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    }

    println(n, x);
    println(a);

    return 0;
}
