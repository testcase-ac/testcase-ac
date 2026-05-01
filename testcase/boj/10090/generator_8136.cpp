#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose size category: small, medium, large
    double p = rnd.next();
    int n;
    if (p < 0.3) {
        // small: easy to verify
        n = rnd.next(2, 10);
    } else if (p < 0.6) {
        // medium: moderate size
        n = rnd.next(11, 50);
    } else {
        // large: closer to input limit but still hand-checkable
        n = rnd.next(51, 100);
    }
    // Prepare sorted permutation
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    // Permutation type: random, sorted, reverse, nearly sorted
    int type = rnd.next(0, 3);
    if (type == 0) {
        // fully random
        shuffle(a.begin(), a.end());
    } else if (type == 1) {
        // sorted: do nothing
    } else if (type == 2) {
        // reverse sorted
        reverse(a.begin(), a.end());
    } else {
        // nearly sorted: few swaps
        int maxSwaps = min(n / 2, 5);
        int swaps = rnd.next(1, maxSwaps);
        for (int i = 0; i < swaps; i++) {
            int x = rnd.next(0, n - 1);
            int y = rnd.next(0, n - 1);
            swap(a[x], a[y]);
        }
    }

    // Output
    println(n);
    println(a);
    return 0;
}
