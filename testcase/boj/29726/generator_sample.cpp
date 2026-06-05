#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(int x) {
    return max(1, min(100000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 6);
    } else {
        n = rnd.next(7, 30);
    }

    int m;
    if (n == 2) {
        m = 0;
    } else if (mode == 2) {
        m = 0;
    } else if (mode == 3) {
        m = n - 2;
    } else if (rnd.next(0, 3) == 0) {
        m = rnd.next(max(0, n - 5), n - 2);
    } else {
        m = rnd.next(0, n - 2);
    }

    vector<int> a(n);
    if (mode == 0) {
        a[0] = rnd.next(1, 100);
        a[1] = rnd.next(99900, 100000);
        if (rnd.next(0, 1)) swap(a[0], a[1]);
    } else if (mode == 1) {
        int base = rnd.next(1, 100000);
        fill(a.begin(), a.end(), base);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) a[i] = clampValue(base + rnd.next(-3, 3));
        }
    } else if (mode == 2) {
        int cur = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            a[i] = cur;
            cur = clampValue(cur + rnd.next(1, 5000));
        }
    } else if (mode == 3) {
        int cur = rnd.next(90000, 100000);
        for (int i = 0; i < n; ++i) {
            a[i] = cur;
            cur = clampValue(cur - rnd.next(1, 5000));
        }
    } else if (mode == 4) {
        int low = rnd.next(1, 200);
        int high = rnd.next(99800, 100000);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? low + rnd.next(0, 30) : high - rnd.next(0, 30);
        }
    } else if (mode == 5) {
        int cur = rnd.next(10000, 90000);
        for (int i = 0; i < n; ++i) {
            cur = clampValue(cur + rnd.next(-9000, 9000));
            a[i] = cur;
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(1000, 99000);
        int left = rnd.next(0, n - 2);
        int right = rnd.next(left + 1, n - 1);
        a[left] = rnd.next(1, 50);
        a[right] = rnd.next(99950, 100000);
    } else {
        int period = rnd.next(2, min(6, n));
        vector<int> pattern(period);
        for (int i = 0; i < period; ++i) pattern[i] = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) a[i] = pattern[i % period];
    }

    println(n, m);
    println(a);
    return 0;
}
