#include "testlib.h"

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int m = 1;
    vector<int> a(n);

    if (mode == 0) {
        m = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-10, 10);
        }
    } else if (mode == 1) {
        m = rnd.next(1, 15);
        int stress = rnd.next(0, max(0, m - 1));
        for (int i = 0; i < n; ++i) {
            int target = rnd.next(max(0, m - 2), m + 2);
            int delta = target - stress;
            delta = max(-10000, min(10000, delta));
            a[i] = delta;
            stress = max(0, stress + delta);
        }
    } else if (mode == 2) {
        m = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a[i] = rnd.next(1, 100);
            } else if (i % 3 == 1) {
                a[i] = -rnd.next(1, 100);
            } else {
                a[i] = rnd.next(-5, 5);
            }
        }
    } else if (mode == 3) {
        m = rnd.next(20, 200);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-3, 3);
        }
    } else if (mode == 4) {
        m = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-10000, 10000);
        }
    } else {
        n = rnd.next(1, 12);
        a.assign(n, 0);
        m = rnd.next(999900000, 1000000000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-10000, 10000);
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", a[i]);
    }
    putchar('\n');

    return 0;
}
