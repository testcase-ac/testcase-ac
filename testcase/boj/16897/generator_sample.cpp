#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

const ll MAXV = 1000000000LL;

ll clampValue(ll x) {
    return max(1LL, min(MAXV, x));
}

pair<ll, ll> dimensionsNearMultiple(ll k) {
    ll block = k + 1;
    ll maxQ = max(1LL, (MAXV - 1) / block);
    ll q = rnd.next(0LL, min(maxQ, 2000000LL));
    ll base = q * block + 1;
    ll a = clampValue(base + rnd.next(-2LL, 3LL));
    ll b = clampValue(base + rnd.next(-2LL, 3LL) + rnd.next(0LL, 7LL));
    if (rnd.next(2)) swap(a, b);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 80);
    vector<tuple<ll, ll, ll>> cases;
    cases.reserve(t);

    cases.emplace_back(1, 1, 1);
    cases.emplace_back(MAXV, MAXV, MAXV);
    cases.emplace_back(1, MAXV, 1);
    cases.emplace_back(MAXV, 1, MAXV);

    while ((int)cases.size() < t) {
        int mode = rnd.next(6);
        ll k, n, m;

        if (mode == 0) {
            k = rnd.next(1LL, 8LL);
            n = rnd.next(1LL, 12LL);
            m = rnd.next(1LL, 12LL);
        } else if (mode == 1) {
            k = rnd.next(1LL, 20LL);
            auto dims = dimensionsNearMultiple(k);
            n = dims.first;
            m = dims.second;
        } else if (mode == 2) {
            k = rnd.next(1LL, 1000000LL);
            n = rnd.next(1LL, min(MAXV, k + rnd.next(0LL, 20LL)));
            m = rnd.next(1LL, min(MAXV, k + rnd.next(0LL, 20LL)));
        } else if (mode == 3) {
            k = rnd.next(MAXV - 1000, MAXV);
            n = rnd.next(1LL, 1000LL);
            m = rnd.next(1LL, 1000LL);
        } else if (mode == 4) {
            k = rnd.next(1LL, MAXV);
            n = rnd.next(MAXV - 1000, MAXV);
            m = rnd.next(1LL, 1000LL);
            if (rnd.next(2)) swap(n, m);
        } else {
            k = rnd.next(1LL, MAXV);
            n = rnd.next(1LL, MAXV);
            m = rnd.next(1LL, MAXV);
        }

        cases.emplace_back(k, n, m);
    }

    shuffle(cases.begin(), cases.end());
    println((int)cases.size());
    for (auto [k, n, m] : cases) println(k, n, m);

    return 0;
}
