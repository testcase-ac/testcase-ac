#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 3);
    } else if (rnd.next(0, 9) == 0) {
        n = rnd.next(30, 80);
    } else {
        n = rnd.next(4, 25);
    }

    vector<int> a(n);

    if (mode == 0) {
        a[0] = rnd.any(vector<int>{1, rnd.next(2, 9999), 10000});
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(vector<int>{1, 10000, rnd.next(1, 10000)});
        }
    } else if (mode == 2) {
        int lo = rnd.next(1, 9000);
        int hi = rnd.next(lo, 10000);
        for (int i = 0; i < n; ++i) {
            a[i] = lo + (hi - lo) * i / max(1, n - 1);
        }
    } else if (mode == 3) {
        int lo = rnd.next(1, 9000);
        int hi = rnd.next(lo, 10000);
        for (int i = 0; i < n; ++i) {
            a[i] = lo + (hi - lo) * (n - 1 - i) / max(1, n - 1);
        }
    } else if (mode == 4) {
        int low = rnd.next(1, 20);
        int high = rnd.next(9980, 10000);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? high - rnd.next(0, 20) : low + rnd.next(0, 20));
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 5) {
        int distinct = rnd.next(1, min(n, 6));
        vector<int> values;
        for (int i = 0; i < distinct; ++i) {
            values.push_back(rnd.next(1, 10000));
        }
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(values);
        }
    } else if (mode == 6) {
        int center = rnd.next(50, 9950);
        int radius = rnd.next(0, min(49, min(center - 1, 10000 - center)));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(center - radius, center + radius);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 10000);
        }
    }

    println(n);
    println(a);

    return 0;
}
