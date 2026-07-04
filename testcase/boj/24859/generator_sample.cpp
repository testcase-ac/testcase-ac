#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int pickValue(int band) {
    if (band == 0) return rnd.next(1, 12);
    if (band == 1) return rnd.next(1, 1000);
    return rnd.next(999999900, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 24);
    int mode = rnd.next(0, 6);
    int band = rnd.next(0, 2);
    vector<int> a(n);

    if (mode == 0) {
        int value = pickValue(band);
        fill(a.begin(), a.end(), value);
    } else if (mode == 1) {
        int current = pickValue(band);
        for (int i = 0; i < n; ++i) {
            current = min(1000000000, current + rnd.next(0, band == 2 ? 10 : 5));
            a[i] = current;
        }
    } else if (mode == 2) {
        int current = pickValue(band);
        for (int i = 0; i < n; ++i) {
            current = max(1, current - rnd.next(0, band == 2 ? 10 : 5));
            a[i] = current;
        }
    } else if (mode == 3) {
        int low = pickValue(0);
        int high = band == 2 ? pickValue(2) : rnd.next(low, max(low, 1000));
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? low : high);
    } else if (mode == 4) {
        int base = pickValue(band);
        fill(a.begin(), a.end(), base);
        int pos = rnd.next(0, n - 1);
        a[pos] = rnd.next(1, 1000000000);
    } else if (mode == 5) {
        int split = rnd.next(0, n - 1);
        int left = pickValue(rnd.next(0, 2));
        int right = pickValue(rnd.next(0, 2));
        for (int i = 0; i < n; ++i) a[i] = (i <= split ? left : right);
    } else {
        int lo = pickValue(rnd.next(0, 1));
        int hi = band == 2 ? pickValue(2) : rnd.next(lo, max(lo, 100000));
        if (lo > hi) swap(lo, hi);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    }

    println(n);
    println(a);
    return 0;
}
