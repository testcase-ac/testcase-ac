#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

long long countInversions(const vector<int>& a) {
    long long result = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = i + 1; j < (int)a.size(); ++j) {
            if (a[i] > a[j]) {
                ++result;
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, 30);

    vector<int> a(n);
    int start = rnd.next(1, 1000000000 - 3 * n);
    for (int i = 0; i < n; ++i) {
        a[i] = start + 3 * i;
    }

    if (mode == 0) {
        // Already sorted: every valid K should produce -1.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, min(n, 8));
        for (int t = 0; t < swaps; ++t) {
            int i = rnd.next(0, n - 2);
            swap(a[i], a[i + 1]);
        }
    } else if (mode == 4) {
        int split = rnd.next(1, n - 1);
        reverse(a.begin(), a.begin() + split);
        reverse(a.begin() + split, a.end());
    } else {
        int len = rnd.next(2, min(n, 10));
        int left = rnd.next(0, n - len);
        reverse(a.begin() + left, a.begin() + left + len);
    }

    long long inv = countInversions(a);
    long long maxK = 1LL * n * n;
    long long k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1 && inv > 0) {
        k = rnd.next(1LL, inv);
    } else if (kMode == 2 && inv < maxK) {
        k = rnd.next(inv + 1, maxK);
    } else if (kMode == 3 && inv > 0) {
        k = inv;
    } else {
        k = rnd.next(1LL, maxK);
    }

    println(n, k);
    println(a);

    return 0;
}
