#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

const ll MAXV = 1000000000LL;

ll pickSmallOrLarge(ll lo, ll hi) {
    if (lo == hi) return lo;
    if (rnd.next(4) != 0 || hi <= 30) return rnd.next(lo, min(hi, 30LL));
    return rnd.next(max(lo, hi - 30), hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    ll n, m, k, other;

    if (mode == 0) {
        n = 1;
        m = pickSmallOrLarge(1, MAXV);
        k = pickSmallOrLarge(1, m);
        other = 0;
    } else if (mode == 1) {
        m = 1;
        n = pickSmallOrLarge(1, MAXV);
        k = 1;
        other = rnd.next(0LL, min(n - 1, 30LL));
    } else if (mode == 2) {
        n = rnd.next(2LL, 15LL);
        m = rnd.next(1LL, 15LL);
        k = rnd.next(1LL, m);
        other = rnd.next(0LL, (n - 1) * m);
    } else if (mode == 3) {
        n = rnd.next(2LL, 40LL);
        m = rnd.next(1LL, 40LL);
        k = rnd.next(1LL, m);
        vector<ll> candidates = {0, 1, max(0LL, m - 1), m, min((n - 1) * m, m + 1),
                                 max(0LL, (n - 1) * m - 1), (n - 1) * m};
        other = rnd.any(candidates);
        other = max(0LL, min(other, (n - 1) * m));
    } else if (mode == 4) {
        n = rnd.next(2LL, 1000000LL);
        m = rnd.next(1LL, 1000000LL);
        k = rnd.next(1LL, m);
        ll q = rnd.next(0LL, n - 1);
        ll r = rnd.next(0LL, m - 1);
        other = q * m + r;
    } else if (mode == 5) {
        n = rnd.next(MAXV - 1000, MAXV);
        m = rnd.next(MAXV - 1000, MAXV);
        k = rnd.next(max(1LL, m - 1000), m);
        other = rnd.next(0LL, 1000000LL);
    } else if (mode == 6) {
        n = rnd.next(MAXV - 1000, MAXV);
        m = rnd.next(MAXV - 1000, MAXV);
        k = rnd.next(1LL, min(m, 1000000LL));
        other = (n - 1) * m - rnd.next(0LL, 1000000LL);
    } else {
        vector<pair<ll, ll>> dimensions = {
            {1, 1},
            {2, 1},
            {2, 5},
            {30, 5},
            {1000000000LL, 1000000000LL},
        };
        auto [dn, dm] = rnd.any(dimensions);
        n = dn;
        m = dm;
        k = rnd.next(1LL, m);
        other = rnd.next(0LL, min((n - 1) * m, 1000000LL));
        if (rnd.next(3) == 0) other = (n - 1) * m;
    }

    ll a = k + other;
    println(n, m, a, k);
    return 0;
}
