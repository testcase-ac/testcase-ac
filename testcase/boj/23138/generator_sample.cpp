#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// Emits compact permutations with varied inversion structure for Swapping Inversions.
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else {
        n = rnd.next(2, 40);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    if (mode == 0) {
        shuffle(p.begin(), p.end());
    } else if (mode == 1) {
        reverse(p.begin(), p.end());
        int swaps = rnd.next(0, min(n, 5));
        for (int i = 0; i < swaps; ++i) {
            swap(p[rnd.next(0, n - 1)], p[rnd.next(0, n - 1)]);
        }
    } else if (mode == 2) {
        int swaps = rnd.next(1, min(n, 8));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            swap(p[a], p[b]);
        }
    } else if (mode == 3) {
        int block = rnd.next(2, min(n, 8));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            if (rnd.next(0, 1) == 0) {
                reverse(p.begin() + l, p.begin() + r);
            } else {
                shuffle(p.begin() + l, p.begin() + r);
            }
        }
    } else if (mode == 4) {
        int shift = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
        if (rnd.next(0, 1) == 0) {
            reverse(p.begin(), p.begin() + shift);
        }
    } else if (mode == 5) {
        vector<int> odds, evens;
        for (int x = 1; x <= n; ++x) {
            if (x % 2 == 1) {
                odds.push_back(x);
            } else {
                evens.push_back(x);
            }
        }
        if (rnd.next(0, 1) == 0) {
            reverse(odds.begin(), odds.end());
        }
        if (rnd.next(0, 1) == 0) {
            reverse(evens.begin(), evens.end());
        }
        p.clear();
        p.insert(p.end(), evens.begin(), evens.end());
        p.insert(p.end(), odds.begin(), odds.end());
    } else {
        int prefix = rnd.next(1, n);
        reverse(p.begin(), p.begin() + prefix);
        int suffix = rnd.next(prefix, n);
        reverse(p.begin() + prefix - 1, p.begin() + suffix);
    }

    println(n);
    println(p);
    return 0;
}
