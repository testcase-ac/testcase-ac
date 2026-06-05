#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long assignmentCount(int l, int r) {
    if (l >= r) return 0;
    int m = (l + r) / 2;
    return assignmentCount(l, m) + assignmentCount(m + 1, r) + (r - l + 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 82) {
        n = rnd.next(5, 35);
    } else {
        n = rnd.next(36, 120);
    }

    long long total = assignmentCount(0, n - 1);
    int kMode = rnd.next(6);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = rnd.next(2, (int)min<long long>(total, 10));
    } else if (kMode == 2) {
        k = rnd.next(1, (int)total);
    } else if (kMode == 3) {
        k = (int)total;
    } else if (kMode == 4) {
        k = (int)min<long long>(100000000LL, total + rnd.next(1, 50));
    } else {
        k = 100000000;
    }

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    int valueMode = rnd.next(5);
    if (valueMode == 1) {
        int step = rnd.next(2, 9);
        int offset = rnd.next(0, 3);
        for (int& x : a) x = x * step + offset;
    } else if (valueMode == 2) {
        int base = rnd.next(999000000, 999999000);
        for (int i = 0; i < n; ++i) a[i] = base + i;
    } else if (valueMode == 3) {
        for (int i = 0; i < n; ++i) a[i] = 1000000000 - i;
    } else if (valueMode == 4) {
        int step = rnd.next(1000, 1000000);
        for (int i = 0; i < n; ++i) a[i] = 1 + i * step;
    }

    int orderMode = rnd.next(7);
    if (orderMode == 0) {
        sort(a.begin(), a.end());
    } else if (orderMode == 1) {
        sort(a.rbegin(), a.rend());
    } else if (orderMode == 2) {
        shuffle(a.begin(), a.end());
    } else if (orderMode == 3) {
        sort(a.begin(), a.end());
        int swaps = rnd.next(1, max(1, n / 5));
        for (int i = 0; i < swaps; ++i) swap(a[rnd.next(n)], a[rnd.next(n)]);
    } else if (orderMode == 4) {
        sort(a.rbegin(), a.rend());
        int swaps = rnd.next(1, max(1, n / 5));
        for (int i = 0; i < swaps; ++i) swap(a[rnd.next(n)], a[rnd.next(n)]);
    } else if (orderMode == 5) {
        rotate(a.begin(), a.begin() + rnd.next(n), a.end());
    } else {
        vector<int> left(a.begin(), a.begin() + n / 2);
        vector<int> right(a.begin() + n / 2, a.end());
        shuffle(left.begin(), left.end());
        shuffle(right.begin(), right.end());
        a.clear();
        a.insert(a.end(), right.begin(), right.end());
        a.insert(a.end(), left.begin(), left.end());
    }

    println(n, k);
    println(a);

    return 0;
}
