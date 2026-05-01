#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for m: small, medium, special large, power-of-ten, or fully random
    int t = rnd.next(0, 4);
    ll m;
    if (t == 0) {
        // Very small m for edge cases
        m = rnd.next(1LL, 50LL);
    } else if (t == 1) {
        // Medium m to test typical behavior
        m = rnd.next(50LL, 1000000LL);
    } else if (t == 2) {
        // Some fixed large values
        vector<ll> bigs = {1000000000LL, 1000000000000LL, 1000000000000000LL, 1000000000000000000LL};
        m = rnd.any(bigs);
    } else if (t == 3) {
        // A random power-of-ten range
        int e = rnd.next(6, 12); // exponent between 6 and 12
        ll lo = 1;
        for (int i = 0; i < e; i++) lo *= 10;
        ll hi = lo * 10 - 1;
        m = rnd.next(lo, hi);
    } else {
        // Fully random up to 1e18
        m = rnd.next(1LL, 1000000000000000000LL);
    }

    // Number of scoring actions
    int n = rnd.next(1, 10);

    // Generate n distinct p values in [1,1000]
    vector<int> pool(1000);
    iota(pool.begin(), pool.end(), 1);
    shuffle(pool.begin(), pool.end());
    vector<int> p(pool.begin(), pool.begin() + n);

    // With some probability, ensure at least one small p to test many-step sums
    if (m >= 2 && rnd.next(1, 100) <= 70) {
        int bound = (m < 10 ? (int)m : 10);
        int smallp = rnd.next(1, bound);
        bool found = false;
        for (int x : p) if (x == smallp) { found = true; break; }
        if (!found) {
            p[rnd.next(0, n - 1)] = smallp;
        }
    }

    // Shuffle the p's so they are not ordered
    shuffle(p.begin(), p.end());

    // Output
    println(m, n);
    for (int x : p) {
        println(x);
    }

    return 0;
}
