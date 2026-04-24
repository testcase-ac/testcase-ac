#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkable tests
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 20);

    vector<int> a(n);

    if (m >= 3) {
        // Create three clusters: small [1..b1], mid [b1+1..b2], large [b2+1..m]
        int b1 = rnd.next(1, m - 2);
        int b2 = rnd.next(b1 + 1, m - 1);

        // Random weights for picking cluster
        int w_small = rnd.next(1, 10);
        int w_mid   = rnd.next(1, 10);
        int w_large = rnd.next(1, 10);
        int total_w = w_small + w_mid + w_large;

        for (int i = 0; i < n; i++) {
            int r = rnd.next(1, total_w);
            if (r <= w_small) {
                a[i] = rnd.next(1, b1);
            } else if (r <= w_small + w_mid) {
                a[i] = rnd.next(b1 + 1, b2);
            } else {
                a[i] = rnd.next(b2 + 1, m);
            }
        }
    } else {
        // If too small for clusters, just uniform
        for (int i = 0; i < n; i++) {
            a[i] = rnd.next(1, m);
        }
    }

    // Occasionally enforce a monotonic sequence for diversity
    if (rnd.next(0, 1) == 1) {
        if (rnd.next(0, 1) == 0)
            sort(a.begin(), a.end());
        else
            sort(a.rbegin(), a.rend());
    }

    // Output
    println(n, m);
    for (int x : a) println(x);

    return 0;
}
