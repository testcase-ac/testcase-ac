#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a = {rnd.next(1, 5000)};
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        int value = rnd.next(1, 5000);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 70);
        int peak = rnd.next(0, n - 1);
        int step = rnd.next(1, max(1, 4500 / n));
        int low = rnd.next(1, 5000 - step * n);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int distance = abs(i - peak);
            a[i] = low + step * (n - distance);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 70);
        int valley = rnd.next(0, n - 1);
        int step = rnd.next(1, max(1, 4500 / n));
        int low = rnd.next(1, 5000 - step * n);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int distance = abs(i - valley);
            a[i] = low + step * distance;
        }
    } else if (mode == 4) {
        n = rnd.next(5, 80);
        int lo = rnd.next(1, 4950);
        int hi = rnd.next(lo, min(5000, lo + rnd.next(0, 50)));
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    } else if (mode == 5) {
        n = rnd.next(5, 90);
        a.resize(n);
        int current = rnd.next(1, 5000);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-4, 4);
            current = min(5000, max(1, current + delta));
            a[i] = current;
        }
    } else {
        n = rnd.next(20, 120);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a[i] = rnd.next(1, 20);
            } else if (i % 3 == 1) {
                a[i] = rnd.next(4980, 5000);
            } else {
                a[i] = rnd.next(1, 5000);
            }
        }
    }

    println(n);
    println(a);

    return 0;
}
