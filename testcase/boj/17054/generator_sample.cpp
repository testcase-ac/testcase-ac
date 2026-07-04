#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(1, 10);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 20);
    } else if (mode == 3) {
        n = rnd.next(1, 20);
        m = rnd.next(1, 25);
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        m = rnd.next(1, 30);
    } else {
        n = rnd.next(1, 50);
        m = rnd.next(1, 50);
    }

    vector<int> p(n);
    int owned = 0;
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            p[i] = rnd.next(0, max(0, m - 1));
        } else if (mode == 1) {
            p[i] = rnd.next(0, m);
        } else if (mode == 2) {
            p[i] = rnd.next() < 0.55 ? 0 : rnd.next(0, m);
        } else if (mode == 3) {
            p[i] = rnd.next() < 0.45 ? m : rnd.next(0, m);
        } else if (mode == 4) {
            p[i] = rnd.next(0, min(m, 2));
        } else {
            p[i] = rnd.wnext(m + 1, rnd.next(-2, 2));
        }
        owned += p[i];
    }

    if (owned == n * m) {
        int idx = rnd.next(n);
        p[idx] = max(0, p[idx] - 1);
        --owned;
    }

    int remaining = n * m - owned;
    int k;
    if (mode == 0) {
        k = remaining;
    } else if (mode == 1) {
        k = 1;
    } else if (mode == 2) {
        k = rnd.next(1, min(remaining, 10));
    } else if (mode == 3) {
        k = rnd.next(max(1, remaining / 2), remaining);
    } else {
        k = rnd.next(1, min(remaining, 500));
    }
    k = min(k, 500);

    vector<int> b(m + 1);
    if (mode == 0) {
        int value = rnd.next(0, 20);
        fill(b.begin(), b.end(), value);
    } else if (mode == 1) {
        for (int i = 0; i <= m; ++i) b[i] = rnd.next(0, 3) * i;
        for (int i = 1; i <= m; ++i) b[i] = max(b[i], b[i - 1]);
    } else if (mode == 2) {
        int value = rnd.next(0, 50);
        for (int i = 0; i <= m; ++i) {
            if (i == m || rnd.next() < 0.25) value += rnd.next(1, 1000);
            b[i] = min(value, 100000);
        }
    } else if (mode == 3) {
        int jumpAt = rnd.next(0, m);
        int low = rnd.next(0, 100);
        int high = rnd.next(low, 100000);
        for (int i = 0; i <= m; ++i) b[i] = i < jumpAt ? low : high;
    } else {
        int value = rnd.next(0, 200);
        for (int i = 0; i <= m; ++i) {
            value += rnd.next(0, 500);
            b[i] = min(value, 100000);
        }
    }

    println(n, m, k);
    println(p);
    println(b);

    return 0;
}
