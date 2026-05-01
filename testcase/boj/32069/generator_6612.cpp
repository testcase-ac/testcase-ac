#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose L in three regimes: small, medium, large
    int L_type = rnd.next(0, 2);
    ll L;
    if (L_type == 0) {
        L = rnd.next(5LL, 50LL);
    } else if (L_type == 1) {
        L = rnd.next(100LL, 500LL);
    } else {
        L = rnd.next(1000000LL, 1000000000000LL);
    }

    // Decide pattern type
    int pattern = rnd.next(0, 3);
    int N;
    vector<ll> A;

    if (pattern == 0) {
        // Single light
        N = 1;
        A.push_back(rnd.next(0LL, L));
    }
    else if (pattern == 1) {
        // Uniform spacing
        N = rnd.next(2, (int)min<ll>(10, L + 1));
        ll step = L / (N - 1);
        for (int i = 0; i < N; i++) {
            A.push_back(step * i);
        }
    }
    else if (pattern == 2) {
        // Random distinct positions
        N = rnd.next(2, (int)min<ll>(10, L + 1));
        set<ll> s;
        while ((int)s.size() < N) {
            s.insert(rnd.next(0LL, L));
        }
        A.assign(s.begin(), s.end());
    }
    else {
        // One tight cluster
        N = rnd.next(2, (int)min<ll>(10, L + 1));
        ll w_min = N - 1;
        ll w_max = min<ll>(L, 50);
        ll w = rnd.next(w_min, w_max);
        ll base = rnd.next(0LL, L - w);
        set<ll> s;
        while ((int)s.size() < N) {
            s.insert(base + rnd.next(0LL, w));
        }
        A.assign(s.begin(), s.end());
    }

    // K: number of smallest darkness values to output
    ll maxK = min<ll>(20, L + 1);
    ll K = rnd.next(1LL, maxK);

    // Output
    println(L, N, K);
    println(A);

    return 0;
}
