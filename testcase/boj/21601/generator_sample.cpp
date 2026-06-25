#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

const ll kMaxN = 1000000000000000000LL;

ll clampValue(ll value) {
    return max(1LL, min(kMaxN, value));
}

ll chooseK(ll n) {
    vector<ll> candidates = {
        1LL,
        min(n, 2LL),
        max(1LL, n / 2),
        min(n, n / 2 + 1),
        max(1LL, n - 1),
        n,
    };

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return rnd.any(candidates);
    }
    if (mode == 1) {
        return rnd.next(1LL, min(n, 30LL));
    }
    if (mode == 2) {
        return rnd.next(max(1LL, n - 30LL), n);
    }
    if (mode == 3) {
        ll center = rnd.next(max(1LL, n / 2 - 20LL), min(n, n / 2 + 20LL));
        return center;
    }
    return rnd.next(1LL, n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    ll n;

    if (mode == 0) {
        n = rnd.next(1LL, 30LL);
    } else if (mode == 1) {
        n = rnd.next(31LL, 1000LL);
    } else if (mode == 2) {
        n = rnd.next(1001LL, 1000000LL);
    } else if (mode == 3) {
        int exponent = rnd.next(0, 59);
        ll base = 1LL << exponent;
        ll delta = rnd.next(-20LL, 20LL);
        n = clampValue(base + delta);
    } else if (mode == 4) {
        n = rnd.next(kMaxN - 1000000LL, kMaxN);
    } else {
        vector<ll> values = {
            1LL, 2LL, 3LL, 4LL, 5LL, 6LL, 7LL, 8LL, 9LL, 10LL,
            15LL, 16LL, 17LL, 31LL, 32LL, 33LL, 63LL, 64LL, 65LL,
            999LL, 1000LL, 1001LL,
            999999LL, 1000000LL, 1000001LL,
            (1LL << 58) - 1LL, 1LL << 58, (1LL << 58) + 1LL,
            (1LL << 59) - 1LL, 1LL << 59, (1LL << 59) + 1LL,
            kMaxN - 2LL, kMaxN - 1LL, kMaxN,
        };
        n = rnd.any(values);
    }

    ll k = chooseK(n);
    println(n, k);

    return 0;
}
