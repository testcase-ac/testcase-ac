#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int nonZeroValue(int lo, int hi) {
    int value = rnd.next(lo, hi);
    if (value == 0) {
        value = rnd.next(0, 1) ? 1 : -1;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int q;

    if (mode == 0) {
        n = 4;
        q = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(5, 8);
        q = rnd.next(n, 3 * n);
    } else if (mode == 2) {
        n = rnd.next(8, 20);
        q = rnd.next(1, 30);
    } else if (mode == 3) {
        n = rnd.next(20, 60);
        q = rnd.next(20, 80);
    } else if (mode == 4) {
        n = rnd.next(4, 12);
        q = rnd.next(50, 120);
    } else if (mode == 5) {
        n = rnd.next(70, 150);
        q = rnd.next(70, 180);
    } else {
        n = rnd.next(4, 35);
        q = rnd.next(1, 120);
    }

    vector<int> a(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? 10 : -10);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(1, 10);
        }
    } else if (mode == 2) {
        int lo = rnd.next(-10, -1);
        int hi = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            a[i] = nonZeroValue(lo, hi);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(vector<int>{-10, -5, -1, 1, 5, 10});
        }
    } else {
        int magnitudeLimit = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            int magnitude = rnd.next(1, magnitudeLimit);
            a[i] = rnd.next(0, 1) ? magnitude : -magnitude;
        }
    }

    vector<int> queries(q);
    if (mode == 0) {
        for (int i = 0; i < q; ++i) {
            queries[i] = rnd.next(1, n);
        }
    } else if (mode == 1) {
        int pivot = rnd.next(1, n);
        for (int i = 0; i < q; ++i) {
            queries[i] = (i % 3 == 0 ? pivot : rnd.next(1, n));
        }
    } else if (mode == 2) {
        vector<int> edge = {1, 2, 3, n - 2, n - 1, n};
        for (int i = 0; i < q; ++i) {
            queries[i] = rnd.any(edge);
        }
    } else if (mode == 3) {
        int step = rnd.next(1, min(n - 1, 7));
        int cur = rnd.next(1, n);
        for (int i = 0; i < q; ++i) {
            queries[i] = cur;
            cur += step;
            while (cur > n) {
                cur -= n;
            }
        }
    } else {
        for (int i = 0; i < q; ++i) {
            queries[i] = rnd.next(1, n);
        }
    }

    println(n, q);
    println(a);
    println(queries);

    return 0;
}
