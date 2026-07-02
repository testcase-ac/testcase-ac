#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(long long value) {
    return static_cast<int>(max(-1000000LL, min(1000000LL, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    if (mode == 5) {
        n = rnd.next(40, 80);
    }

    int k;
    if (mode == 0) {
        k = 0;
    } else if (mode == 1) {
        k = n;
    } else if (mode == 2) {
        k = rnd.next(1, max(1, n / 3));
    } else {
        k = rnd.next(0, n);
    }

    vector<int> a(n), b(n);
    int base = rnd.next(-50, 50);
    int shift = rnd.next(-100, 100);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-30, 30);
            b[i] = clampValue(static_cast<long long>(a[i]) + shift + rnd.next(-8, 8));
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-1000000, 1000000);
            b[i] = rnd.next(-1000000, 1000000);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int delta = (i % 2 == 0 ? shift : -shift) + rnd.next(-3, 3);
            a[i] = base + rnd.next(-10, 10);
            b[i] = clampValue(static_cast<long long>(a[i]) + delta);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 3 == 0 ? -1000000 : rnd.next(-20, 20));
            b[i] = (i % 4 == 0 ? 1000000 : clampValue(static_cast<long long>(a[i]) + shift));
        }
    } else if (mode == 4) {
        vector<int> choices = {-7, -3, -1, 0, 1, 3, 7};
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(choices);
            b[i] = clampValue(static_cast<long long>(a[i]) + rnd.any(choices) + shift);
        }
        shuffle(a.begin(), a.end());
        shuffle(b.begin(), b.end());
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-200, 200);
            b[i] = clampValue(static_cast<long long>(a[i]) + (i % 5) * shift + rnd.next(-20, 20));
        }
    }

    println(n, k);
    println(a);
    println(b);

    return 0;
}
