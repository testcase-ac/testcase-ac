#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(7, 18);
        m = rnd.next(n, min(60, n * (n + 1) / 2));
    } else if (mode == 2) {
        n = rnd.next(12, 28);
        m = rnd.next(1, n);
    } else if (mode == 3) {
        n = rnd.next(18, 45);
        m = rnd.next(20, 90);
    } else if (mode == 4) {
        n = rnd.next(40, 90);
        m = rnd.next(n / 2, n * 2);
    } else {
        n = rnd.next(2, 12);
        m = rnd.next(1, min(200, n * n));
    }

    vector<long long> a(n);
    int valueMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        if (valueMode == 0) {
            a[i] = rnd.next(1, 20);
        } else if (valueMode == 1) {
            a[i] = (i % 2 == 0) ? rnd.next(1, 5) : rnd.next(900000000, 1000000000);
        } else if (valueMode == 2) {
            a[i] = i + 1;
        } else if (valueMode == 3) {
            a[i] = n - i;
        } else {
            a[i] = rnd.next(1, 1000000000);
        }
    }

    vector<pair<int, int>> intervals;
    intervals.reserve(m);
    for (int i = 0; i < m; ++i) {
        int l;
        int r;
        int intervalMode = rnd.next(0, 5);

        if (intervalMode == 0) {
            l = r = rnd.next(1, n);
        } else if (intervalMode == 1) {
            l = rnd.next(1, n);
            r = min(n, l + rnd.next(0, min(4, n - l)));
        } else if (intervalMode == 2) {
            r = rnd.next(1, n);
            l = max(1, r - rnd.next(0, min(4, r - 1)));
        } else if (intervalMode == 3) {
            l = 1;
            r = rnd.next(1, n);
        } else if (intervalMode == 4) {
            l = rnd.next(1, n);
            r = n;
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }

        intervals.push_back({l, r});
    }

    shuffle(intervals.begin(), intervals.end());

    println(n, m);
    println(a);
    for (auto [l, r] : intervals) {
        println(l, r);
    }

    return 0;
}
