#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 2) {
        n = rnd.next(2, 8);
    } else if (sizeMode <= 4) {
        n = rnd.next(9, 25);
    } else {
        n = rnd.next(26, 60);
    }

    int qMode = rnd.next(0, 4);
    int q;
    if (qMode == 0) {
        q = 1;
    } else if (qMode == 1) {
        q = rnd.next(2, min(10, n + 3));
    } else if (qMode == 2) {
        q = rnd.next(10, 40);
    } else if (qMode == 3) {
        q = n;
    } else {
        q = rnd.next(40, 90);
    }

    vector<int> a(n);
    int valueMode = rnd.next(0, 4);
    if (valueMode == 0) {
        int x = rnd.next(1, 20);
        fill(a.begin(), a.end(), x);
    } else if (valueMode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = i + 1;
        }
        shuffle(a.begin(), a.end());
    } else if (valueMode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 100);
        }
    } else if (valueMode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(99999950, 100000000);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = (rnd.next(0, 4) == 0) ? rnd.next(1000000, 100000000) : rnd.next(1, 30);
        }
    }

    println(n, q);
    println(a);

    int queryMode = rnd.next(0, 5);
    for (int i = 0; i < q; ++i) {
        int l, r;
        if (queryMode == 0) {
            l = rnd.next(1, n);
            r = l;
        } else if (queryMode == 1) {
            l = 1;
            r = n;
        } else if (queryMode == 2) {
            l = 1;
            r = rnd.next(1, n);
        } else if (queryMode == 3) {
            l = rnd.next(1, n);
            r = n;
        } else if (queryMode == 4) {
            l = rnd.next(1, n);
            int len = rnd.next(1, min(5, n - l + 1));
            r = l + len - 1;
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }
        println(l, r);
    }

    return 0;
}
