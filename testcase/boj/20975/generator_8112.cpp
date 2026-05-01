#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for N: bias towards small or large
    bool smallN = rnd.next(0, 1) == 0;
    int N = smallN ? rnd.wnext(20, -2) + 1 : rnd.wnext(20, 2) + 1;

    // Hyperparameter for maximum height
    int r = rnd.next(0, 4);
    ll max_h;
    if (r == 0) max_h = 10LL;
    else if (r == 1) max_h = 100LL;
    else if (r == 2) max_h = 1000LL;
    else if (r == 3) max_h = 1000000LL;
    else max_h = 1000000000LL;

    // Generate cow heights
    vector<ll> a(N), b(N);
    bool uniformA = rnd.next(0, 9) == 0;
    if (uniformA) {
        ll v = rnd.next(1LL, max_h);
        for (int i = 0; i < N; i++) a[i] = v;
    } else {
        for (int i = 0; i < N; i++) a[i] = rnd.next(1LL, max_h);
    }

    // Generate stall limits with three modes for variability
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // Pure random
        for (int i = 0; i < N; i++) b[i] = rnd.next(1LL, max_h);
    } else if (mode == 1) {
        // Generous: based on cows + small offset
        vector<ll> perm = a;
        shuffle(perm.begin(), perm.end());
        ll delta = max_h / 10;
        for (int i = 0; i < N; i++) {
            ll off = (delta > 0 ? rnd.next(0LL, delta) : 0LL);
            b[i] = min(perm[i] + off, max_h);
        }
    } else {
        // Restrictive: bias lower, ensure some impossible stalls
        for (int i = 0; i < N; i++) b[i] = rnd.next(1LL, max_h / 2);
        if (N >= 3) {
            ll amin = *min_element(a.begin(), a.end());
            int cnt = rnd.next(1, max(1, N / 3));
            vector<int> idx(N);
            iota(idx.begin(), idx.end(), 0);
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < cnt; i++) {
                int j = idx[i];
                ll upper = (amin > 1 ? amin - 1 : 1);
                b[j] = rnd.next(1LL, upper);
            }
        }
    }

    // Output
    println(N);
    println(a);
    println(b);
    return 0;
}
