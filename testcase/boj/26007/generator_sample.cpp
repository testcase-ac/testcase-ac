#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    int m = rnd.next(1, 40);
    int x = rnd.next(-50, 50);
    vector<int> a(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-10, 10);
        }
    } else if (mode == 1) {
        int sign = rnd.next(0, 1) ? 1 : -1;
        for (int i = 0; i < n; ++i) {
            a[i] = sign * rnd.next(0, 20);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(0, 30);
        }
    } else if (mode == 3) {
        int drift = rnd.next(-4, 4);
        for (int i = 0; i < n; ++i) {
            a[i] = drift + rnd.next(-3, 3);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 5) == 0 ? rnd.next(-10000, 10000) : rnd.next(-20, 20);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = 0;
        }
    }

    vector<int> rating(n + 1);
    rating[0] = x;
    for (int i = 1; i <= n; ++i) {
        rating[i] = rating[i - 1] + a[i - 1];
    }

    int k;
    int kMode = rnd.next(0, 3);
    if (kMode == 0) {
        k = rating[rnd.next(0, n)];
    } else if (kMode == 1) {
        k = rating[rnd.next(0, n)] + rnd.next(-2, 2);
    } else if (kMode == 2) {
        k = *min_element(rating.begin(), rating.end()) - rnd.next(0, 5);
    } else {
        k = *max_element(rating.begin(), rating.end()) + rnd.next(0, 5);
    }

    println(n, m, k, x);
    println(a);

    for (int i = 0; i < m; ++i) {
        int l, r;
        int queryMode = rnd.next(0, 4);
        if (queryMode == 0) {
            l = 1;
            r = n + 1;
        } else if (queryMode == 1) {
            l = rnd.next(1, n);
            r = l + 1;
        } else if (queryMode == 2) {
            l = rnd.next(1, n);
            r = rnd.next(l + 1, n + 1);
        } else if (queryMode == 3) {
            r = n + 1;
            l = rnd.next(1, n);
        } else {
            l = rnd.next(1, n);
            int len = rnd.next(1, min(5, n - l + 1));
            r = l + len;
        }
        println(l, r);
    }

    return 0;
}
