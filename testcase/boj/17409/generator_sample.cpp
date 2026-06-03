#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    return a;
}

static void applyRandomSwaps(vector<int>& a, int swaps) {
    int n = int(a.size());
    for (int i = 0; i < swaps; ++i) {
        int x = rnd.next(0, n - 1);
        int y = rnd.next(0, n - 1);
        swap(a[x], a[y]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = rnd.next(1, 6);
    } else if (sizeMode <= 3) {
        n = rnd.next(7, 35);
    } else if (sizeMode == 4) {
        n = rnd.next(36, 120);
    } else {
        n = rnd.next(121, 300);
    }

    int k;
    if (rnd.next(0, 4) == 0) {
        k = rnd.next(1, 10);
    } else {
        k = rnd.next(1, min(10, n));
    }

    vector<int> a = identityPermutation(n);
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        // Already increasing: maximum number of increasing subsequences.
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, max(1, n / 4));
        applyRandomSwaps(a, swaps);
    } else if (mode == 4) {
        int block = rnd.next(2, min(n, 12));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            reverse(a.begin() + l, a.begin() + r);
        }
    } else if (mode == 5) {
        int shift = rnd.next(0, n - 1);
        rotate(a.begin(), a.begin() + shift, a.end());
    } else if (mode == 6) {
        vector<int> b;
        int lo = 1, hi = n;
        while (lo <= hi) {
            b.push_back(hi--);
            if (lo <= hi) {
                b.push_back(lo++);
            }
        }
        a = b;
    } else {
        vector<int> b;
        int lo = 1, hi = n;
        while (lo <= hi) {
            if (rnd.next(0, 1) == 0) {
                b.push_back(lo++);
            } else {
                b.push_back(hi--);
            }
        }
        a = b;
    }

    println(n, k);
    println(a);

    return 0;
}
