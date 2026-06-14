#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedXorPartner(int k) {
    for (int tries = 0; tries < 1000; ++tries) {
        int x = rnd.next(0, 100000);
        if ((x ^ k) <= 100000) return x;
    }

    for (int x = 0; x <= 100000; ++x) {
        if ((x ^ k) <= 100000) return x;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 8);
    } else if (mode == 5) {
        n = rnd.next(300, 2000);
    } else {
        n = rnd.next(8, 80);
    }

    int m = rnd.next(1, n - 1);
    int k = rnd.next(0, (1 << 17) - 1);
    vector<int> a(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 15);
        if (rnd.next(0, 1)) k = rnd.next(0, 15);
    } else if (mode == 1) {
        k = 0;
        int base = rnd.next(0, 100000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a[i] = rnd.next(0, 100000);
            } else {
                a[i] = base;
            }
        }
    } else if (mode == 2) {
        k = rnd.next(0, 100000);
        int x = boundedXorPartner(k);
        int y = x ^ k;
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 100000);
        for (int i = 0; i + 1 < n; i += rnd.next(2, 7)) {
            int gap = rnd.next(1, min(m, n - 1 - i));
            a[i] = x;
            a[i + gap] = y;
        }
    } else if (mode == 3) {
        k = rnd.next(0, 100000);
        int x = boundedXorPartner(k);
        int y = x ^ k;
        m = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 100000);
        for (int i = 0; i + m + 1 < n; i += rnd.next(m + 1, min(n - i - 1, m + 6))) {
            a[i] = x;
            a[i + m + 1] = y;
        }
    } else if (mode == 4) {
        int hi = rnd.next(1, 100000);
        int lo = rnd.next(0, hi);
        if (hi - lo > 300) hi = lo + rnd.next(0, 300);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    } else {
        int block = rnd.next(2, 30);
        vector<int> values(block);
        for (int& value : values) value = rnd.next(0, 100000);
        for (int i = 0; i < n; ++i) a[i] = values[i % block];
        if (rnd.next(0, 2) == 0) k = values[rnd.next(0, block - 1)] ^ values[rnd.next(0, block - 1)];
        m = rnd.next(max(1, block / 2), n - 1);
    }

    println(n, m, k);
    println(a);

    return 0;
}
