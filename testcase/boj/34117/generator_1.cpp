#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 8);
    } else if (sizeMode == 2) {
        n = rnd.next(9, 25);
    } else if (sizeMode == 3) {
        n = rnd.next(26, 80);
    } else if (sizeMode == 4) {
        n = rnd.next(81, 200);
    } else {
        n = rnd.next(201, 500);
    }

    int mode = rnd.next(0, 8);
    long long p;
    vector<int> a(n);

    if (mode == 0) {
        p = rnd.next(1, max(1, n + 5));
        fill(a.begin(), a.end(), 1);
    } else if (mode == 1) {
        p = rnd.next(1, 1000000000);
        int value = (p == 1000000000 ? 1000000000 : rnd.next((int)p + 1, 1000000000));
        fill(a.begin(), a.end(), value);
    } else if (mode == 2) {
        p = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(2, 3);
        }
    } else if (mode == 3) {
        p = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 50);
        }
    } else if (mode == 4) {
        p = rnd.next(1, 1000000000);
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 10);
            a[i] = cur;
        }
    } else if (mode == 5) {
        p = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? rnd.next(1, 20) : rnd.next(999999900, 1000000000));
        }
    } else if (mode == 6) {
        p = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            int choice = rnd.next(0, 4);
            if (choice == 0) {
                a[i] = 1;
            } else if (choice == 1) {
                a[i] = min(1000000000LL, p);
            } else if (choice == 2) {
                a[i] = (p == 1000000000 ? 1000000000 : (int)p + 1);
            } else if (choice == 3) {
                a[i] = rnd.next(1, 1000);
            } else {
                a[i] = rnd.next(999999000, 1000000000);
            }
        }
    } else if (mode == 7) {
        p = rnd.next(1, min(1000000000, max(1, 3 * n)));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 10);
        }
    } else {
        p = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 1000000000);
        }
    }

    if (rnd.next(0, 9) == 0) {
        p = 1;
    } else if (rnd.next(0, 9) == 0) {
        p = 1000000000;
    }

    println(n, p);
    println(a);
    return 0;
}
