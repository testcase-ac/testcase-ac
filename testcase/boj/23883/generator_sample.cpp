#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, 40);
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(41, 120);
    }

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        // Already sorted: selection sort performs no swaps.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, min(n, 8));
        for (int t = 0; t < swaps; ++t) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 1);
            swap(a[i], a[j]);
        }
    } else if (mode == 4) {
        shuffle(a.begin(), a.end());
        int fixedSuffix = rnd.next(1, min(n - 1, 10));
        vector<int> suffix;
        for (int value = n - fixedSuffix + 1; value <= n; ++value) {
            suffix.push_back(value);
        }
        int p = 0;
        for (int i = 0; i < n && p < fixedSuffix; ++i) {
            if (a[i] > n - fixedSuffix) {
                a[i] = suffix[p++];
            }
        }
        sort(a.end() - fixedSuffix, a.end());
    } else {
        int pivot = rnd.next(1, n - 2);
        reverse(a.begin(), a.begin() + pivot);
        shuffle(a.begin() + pivot, a.end());
    }

    if (rnd.next(0, 1)) {
        int base = 1000000000 - n - rnd.next(0, 1000);
        for (int& value : a) {
            value += base;
        }
    } else if (rnd.next(0, 3) == 0) {
        int scale = rnd.next(2, 20);
        int offset = rnd.next(0, 100);
        for (int& value : a) {
            value = value * scale + offset;
        }
    }

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = n;
    } else if (kMode == 2) {
        k = max(1, n - 1);
    } else {
        k = rnd.next(1, n);
    }

    println(n, k);
    println(a);

    return 0;
}
