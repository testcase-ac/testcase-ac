#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> increasingPermutation(int n) {
    vector<int> h(n);
    iota(h.begin(), h.end(), 1);
    return h;
}

static vector<int> highLowInterleave(int n) {
    vector<int> h;
    int lo = 1;
    int hi = n;
    bool takeHigh = rnd.next(2);
    while (lo <= hi) {
        if (takeHigh) {
            h.push_back(hi--);
        } else {
            h.push_back(lo++);
        }
        takeHigh = !takeHigh;
    }
    return h;
}

static vector<int> blockShuffle(int n) {
    vector<int> h = increasingPermutation(n);
    int blockSize = rnd.next(2, min(n, 12));
    for (int l = 0; l < n; l += blockSize) {
        int r = min(n, l + blockSize);
        if (rnd.next(2)) {
            reverse(h.begin() + l, h.begin() + r);
        } else {
            shuffle(h.begin() + l, h.begin() + r);
        }
    }
    if (rnd.next(2)) {
        reverse(h.begin(), h.end());
    }
    return h;
}

static vector<int> nearSortedWithSwaps(int n) {
    vector<int> h = increasingPermutation(n);
    int swaps = rnd.next(1, max(1, n / 2));
    for (int i = 0; i < swaps; ++i) {
        int pos = rnd.next(0, n - 2);
        swap(h[pos], h[pos + 1]);
    }
    return h;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(3, 9);
    } else if (mode == 1) {
        n = rnd.next(10, 40);
    } else if (mode == 2) {
        n = rnd.next(41, 120);
    } else {
        n = rnd.next(3, 80);
    }

    vector<int> h;
    if (mode == 0) {
        h = increasingPermutation(n);
        shuffle(h.begin(), h.end());
    } else if (mode == 1) {
        h = increasingPermutation(n);
        reverse(h.begin(), h.end());
        int tweaks = rnd.next(1, n / 3);
        for (int i = 0; i < tweaks; ++i) {
            swap(h[rnd.next(n)], h[rnd.next(n)]);
        }
    } else if (mode == 2) {
        h = highLowInterleave(n);
    } else if (mode == 3) {
        h = blockShuffle(n);
    } else if (mode == 4) {
        h = nearSortedWithSwaps(n);
    } else {
        h = increasingPermutation(n);
        int pivot = rnd.next(1, n - 1);
        rotate(h.begin(), h.begin() + pivot, h.end());
        if (rnd.next(2)) {
            reverse(h.begin(), h.begin() + rnd.next(1, n));
        }
    }

    println(n);
    println(h);
    return 0;
}
