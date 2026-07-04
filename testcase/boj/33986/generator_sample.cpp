#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

static void applyRandomReversals(vector<int>& p, int count) {
    int n = static_cast<int>(p.size());
    for (int i = 0; i < count; ++i) {
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        reverse(p.begin() + l, p.begin() + r + 1);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (rnd.next(0, 9) == 0) {
        n = rnd.next(31, 80);
    } else {
        n = rnd.next(2, 30);
    }

    vector<int> p = identityPermutation(n);

    if (mode == 0) {
        if (rnd.next(0, 1) == 1) {
            applyRandomReversals(p, rnd.next(0, 2));
        }
    } else if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        int shifts = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + shifts, p.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, min(n - 1, 8));
        for (int i = 0; i < swaps; ++i) {
            int pos = rnd.next(0, n - 2);
            swap(p[pos], p[pos + 1]);
        }
    } else if (mode == 4) {
        applyRandomReversals(p, rnd.next(1, min(n, 10)));
    } else if (mode == 5) {
        int blockSize = rnd.next(2, min(n, 8));
        for (int start = 0; start < n; start += blockSize) {
            int end = min(n, start + blockSize);
            if (rnd.next(0, 1) == 1) {
                reverse(p.begin() + start, p.begin() + end);
            }
        }
        if (rnd.next(0, 1) == 1) {
            reverse(p.begin(), p.end());
        }
    } else {
        shuffle(p.begin(), p.end());
    }

    println(n);
    println(p);
    return 0;
}
