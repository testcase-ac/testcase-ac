#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of balls
    int n = rnd.next(1, 10);

    // Choose a pattern type for diversity
    // 0: completely random
    // 1: sorted ascending
    // 2: sorted descending
    // 3: partially sorted (one segment shuffled)
    // 4: many duplicates with shuffle
    int type = rnd.next(0, 4);

    vector<int> a(n);
    if (type == 0) {
        // random values
        for (int i = 0; i < n; i++) {
            a[i] = rnd.next(1, 100);
        }
    } else if (type == 1) {
        // sorted ascending
        int cur = rnd.next(1, 10);
        for (int i = 0; i < n; i++) {
            cur += rnd.next(0, 10);
            a[i] = cur;
        }
    } else if (type == 2) {
        // sorted descending
        int cur = rnd.next(1, 10) + n * 10;
        for (int i = 0; i < n; i++) {
            cur -= rnd.next(0, 10);
            a[i] = max(1, cur);
        }
    } else if (type == 3) {
        // partially sorted: build ascending then shuffle a segment
        int cur = rnd.next(1, 10);
        for (int i = 0; i < n; i++) {
            cur += rnd.next(0, 10);
            a[i] = cur;
        }
        if (n > 1) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, n);
            shuffle(a.begin() + (l-1), a.begin() + r);
        }
    } else {
        // many duplicates: few distinct values, then shuffle
        int distinctV = rnd.next(1, max(1, n/2));
        vector<int> pool(distinctV);
        for (int i = 0; i < distinctV; i++) {
            pool[i] = rnd.next(1, 20);
        }
        for (int i = 0; i < n; i++) {
            a[i] = rnd.any(pool);
        }
        shuffle(a.begin(), a.end());
    }

    // Output
    println(n);
    for (int v : a) {
        println(v);
    }
    return 0;
}
