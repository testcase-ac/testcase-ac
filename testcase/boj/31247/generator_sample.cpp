#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

const ll MAX_VALUE = 1000000000000000000LL;

ll clampValue(ll x) {
    return max(1LL, min(MAX_VALUE, x));
}

ll randomSmallK() {
    return rnd.next(0, 12);
}

ll randomLargeK() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return rnd.next(55, 65);
    if (mode == 1) return rnd.next(66, 1000);
    if (mode == 2) return MAX_VALUE - rnd.next(0, 1000);
    return rnd.next(0LL, MAX_VALUE);
}

ll randomNForK(ll k) {
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        return rnd.next(1LL, 1000LL);
    }
    if (mode == 1) {
        return rnd.next(1LL, MAX_VALUE);
    }
    if (mode == 2) {
        return MAX_VALUE - rnd.next(0, 1000000);
    }

    int e = rnd.next(0, 60);
    ll p = 1LL << e;
    if (mode == 3) {
        return clampValue(p + rnd.next(-3LL, 3LL));
    }
    if (mode == 4) {
        ll scale = rnd.next(1LL, 20LL);
        return clampValue(p * scale + rnd.next(-5LL, 5LL));
    }

    if (k <= 60) {
        ll base = 1LL << (int)k;
        if (base > MAX_VALUE) {
            return rnd.next(1LL, MAX_VALUE);
        }
        ll scale = rnd.next(1LL, min(30LL, MAX_VALUE / base));
        return clampValue(base * scale + rnd.next(-3LL, 3LL));
    }
    return rnd.next(1LL, MAX_VALUE);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    if (mode == 0) {
        t = rnd.next(1, 8);
    } else if (mode <= 3) {
        t = rnd.next(10, 40);
    } else {
        t = rnd.next(60, 120);
    }

    vector<pair<ll, ll>> tests;
    tests.reserve(t);

    vector<pair<ll, ll>> anchors = {
        {1, 0},
        {2, 0},
        {2, 1},
        {3, 1},
        {8, 3},
        {16, 3},
        {17, 4},
        {MAX_VALUE, 0},
        {MAX_VALUE, 60},
        {MAX_VALUE, 61},
        {MAX_VALUE, MAX_VALUE},
    };
    shuffle(anchors.begin(), anchors.end());

    int anchored = min(t, rnd.next(0, min((int)anchors.size(), max(1, t / 3))));
    for (int i = 0; i < anchored; ++i) {
        tests.push_back(anchors[i]);
    }

    while ((int)tests.size() < t) {
        ll k;
        int kMode = rnd.next(0, 4);
        if (kMode <= 1) {
            k = randomSmallK();
        } else if (kMode == 2) {
            k = rnd.next(0, 60);
        } else {
            k = randomLargeK();
        }
        tests.push_back({randomNForK(k), k});
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (auto [n, k] : tests) {
        println(n, k);
    }

    return 0;
}
