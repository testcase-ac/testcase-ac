#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

pair<ll, ll> makeCase(int mode) {
    const ll LIMIT = 1000000000000000000LL;

    if (mode == 0) {
        ll k = rnd.next(1LL, 80LL);
        return rnd.next(0, 1) == 0 ? make_pair(1LL, k) : make_pair(k, 1LL);
    }

    if (mode == 1) {
        ll side = rnd.next(2LL, 64LL);
        return make_pair(side, side);
    }

    if (mode == 2) {
        ll n = rnd.next(2LL, 65LL);
        ll m = rnd.next(2LL, 65LL);
        if (n % 2 == 0) ++n;
        if (m % 2 == 0) ++m;
        return make_pair(n, m);
    }

    if (mode == 3) {
        ll n = rnd.next(2LL, 32LL);
        ll m = rnd.next(33LL, 128LL);
        return rnd.next(0, 1) == 0 ? make_pair(n, m) : make_pair(m, n);
    }

    if (mode == 4) {
        ll base = 1LL << rnd.next(1, 10);
        ll n = base + rnd.next(-1LL, 1LL);
        ll m = (1LL << rnd.next(1, 10)) + rnd.next(-1LL, 1LL);
        return make_pair(max(1LL, n), max(1LL, m));
    }

    if (mode == 5) {
        vector<ll> values = {1LL, 2LL, 3LL, 4LL, 5LL, 999999937LL, 1000000000LL, LIMIT - 1, LIMIT};
        ll n = rnd.any(values);
        ll m = rnd.any(values);
        return make_pair(n, m);
    }

    ll n = rnd.next(1LL, 1000LL);
    ll m = rnd.next(1LL, 1000LL);
    return make_pair(n, m);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 24);
    println(t);

    for (int i = 0; i < t; ++i) {
        int mode = i < 6 ? i : rnd.next(0, 6);
        auto [n, m] = makeCase(mode);
        println(n, m);
    }

    return 0;
}
