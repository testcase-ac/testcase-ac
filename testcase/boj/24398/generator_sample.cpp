#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode <= 2) {
        n = rnd.next(5, 12);
    } else if (mode <= 5) {
        n = rnd.next(13, 40);
    } else {
        n = rnd.next(41, 120);
    }

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int rotations = rnd.next(0, n - 1);
        rotate(a.begin(), a.begin() + rotations, a.end());
    } else if (mode == 3) {
        for (int blockStart = 0; blockStart < n; blockStart += rnd.next(2, 6)) {
            int blockEnd = min(n, blockStart + rnd.next(2, 7));
            shuffle(a.begin() + blockStart, a.begin() + blockEnd);
        }
    } else if (mode == 4) {
        vector<int> b;
        int lo = 0, hi = n - 1;
        while (lo <= hi) {
            if (rnd.next(0, 1) == 0) {
                b.push_back(a[lo++]);
            } else {
                b.push_back(a[hi--]);
            }
        }
        a = b;
    } else if (mode == 5) {
        stable_sort(a.begin(), a.end(), [](int x, int y) {
            return (x % 3 == y % 3) ? x < y : x % 3 < y % 3;
        });
        int swaps = rnd.next(n / 4, n);
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(0, n - 1)], a[rnd.next(0, n - 1)]);
        }
    } else {
        shuffle(a.begin(), a.end());
        sort(a.begin(), a.begin() + rnd.next(1, n / 2 + 1));
        sort(a.begin() + rnd.next(n / 2, n - 1), a.end(), greater<int>());
    }

    int scaleMode = rnd.next(0, 3);
    if (scaleMode == 1) {
        int offset = rnd.next(1, 1000);
        int step = rnd.next(2, 1000);
        for (int& x : a) {
            x = offset + x * step;
        }
    } else if (scaleMode == 2) {
        for (int& x : a) {
            x = 1000000000 - x + 1;
        }
    } else if (scaleMode == 3) {
        int base = rnd.next(1, 1000000000 - n * 10);
        int step = rnd.next(1, 10);
        for (int& x : a) {
            x = base + x * step;
        }
    }

    int qMode = rnd.next(0, 4);
    int q;
    if (qMode == 0) {
        q = 1;
    } else if (qMode == 1) {
        q = n;
    } else if (qMode == 2) {
        q = (n + 1) / 2;
    } else {
        q = rnd.next(1, n);
    }

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = rnd.next(2, min(100, n * n));
    } else if (kMode == 2) {
        k = rnd.next(1000, 1000000);
    } else if (kMode == 3) {
        k = 100000000;
    } else {
        k = rnd.next(1, 100000000);
    }

    println(n, q, k);
    println(a);

    return 0;
}
