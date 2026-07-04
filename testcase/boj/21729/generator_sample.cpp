#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

const ll MAX_N = 20000000000LL;
const ll MOD = 1000003LL;

ll clampN(ll n) {
    return max(1LL, min(MAX_N, n));
}

ll chooseN(int mode) {
    if (mode == 0) {
        return rnd.next(1LL, 20LL);
    }
    if (mode == 1) {
        return rnd.next(21LL, 1000LL);
    }
    if (mode == 2) {
        ll q = rnd.next(0LL, MAX_N / MOD);
        ll delta = rnd.next(-5LL, 5LL);
        return clampN(q * MOD + delta);
    }
    if (mode == 3) {
        return clampN(MAX_N - rnd.next(0LL, 10000LL));
    }
    if (mode == 4) {
        ll p = rnd.next(1LL, 2000000LL);
        return clampN(p * p + rnd.next(-20LL, 20LL));
    }
    return rnd.next(1LL, MAX_N);
}

ll chooseK(ll n, int mode) {
    ll maxK = 2 * n;
    if (mode == 0) {
        vector<ll> candidates = {0, 1, 2, maxK / 2, maxK - 2, maxK - 1, maxK};
        vector<ll> valid;
        for (ll x : candidates) {
            if (0 <= x && x <= maxK) {
                valid.push_back(x);
            }
        }
        return rnd.any(valid);
    }
    if (mode == 1) {
        return rnd.next(0LL, min(maxK, 50LL));
    }
    if (mode == 2) {
        return maxK - rnd.next(0LL, min(maxK, 50LL));
    }
    if (mode == 3) {
        ll q = rnd.next(0LL, maxK / MOD);
        ll delta = rnd.next(-5LL, 5LL);
        return max(0LL, min(maxK, q * MOD + delta));
    }
    return rnd.next(0LL, maxK);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        ll n = chooseN(mode);
        ll k = chooseK(n, rnd.next(0, 4));
        println(n, k);
    }

    return 0;
}
