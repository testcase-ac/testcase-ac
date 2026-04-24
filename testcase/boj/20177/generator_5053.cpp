#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for sizes
    int n = rnd.next(2, 10);
    int m = rnd.next(1, 20);

    // Generate fluctuation values with diverse magnitudes
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        int t = rnd.next(0, 2);
        if (t == 0) {
            a[i] = rnd.next(-10, 10);
        } else if (t == 1) {
            a[i] = rnd.next(-1000, 1000);
        } else {
            a[i] = rnd.next(-1000000000LL, 1000000000LL);
        }
    }

    // Prefix sums for optional query bounds
    vector<ll> ps(n+1, 0);
    for (int i = 1; i <= n; i++) {
        ps[i] = ps[i-1] + a[i-1];
    }

    // Output header
    println(n, m);
    println(a);

    // Generate queries
    const ll UMAX = 100000000000000LL; // 1e14
    for (int i = 0; i < m; i++) {
        int S = rnd.next(1, n);
        int E = rnd.next(S, n);
        ll U;
        int utype = rnd.next(0, 3);
        if (utype == 0) {
            U = rnd.next(-100LL, 100LL);
        } else if (utype == 1) {
            U = rnd.next(-10000LL, 10000LL);
        } else if (utype == 2) {
            U = rnd.next(-UMAX, UMAX);
        } else {
            // set U to the exact sum of [S, E]
            U = ps[E] - ps[S-1];
        }
        println(S, E, U);
    }
    return 0;
}
