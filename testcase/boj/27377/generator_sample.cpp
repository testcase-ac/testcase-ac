#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;

const ll MAX_N = 1000000000000000000LL;
const ll MAX_COST = 1000000000LL;

ll clampN(ll x) {
    return max(1LL, min(MAX_N, x));
}

ll randomCost(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(1, 100000);
    if (mode == 2) return rnd.next(MAX_COST - 1000, MAX_COST);
    return rnd.next(1LL, MAX_COST);
}

ll randomN() {
    int mode = rnd.next(0, 8);
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(1, 1000000);
    if (mode == 2) {
        int k = rnd.next(0, 59);
        return 1LL << k;
    }
    if (mode == 3) {
        int k = rnd.next(1, 59);
        ll base = 1LL << k;
        return clampN(base + rnd.next(-3, 3));
    }
    if (mode == 4) {
        ll high = rnd.next(1LL, 1000000000LL);
        ll low = rnd.next(0LL, 1000000000LL);
        return clampN(high * 1000000000LL + low);
    }
    if (mode == 5) return rnd.next(MAX_N - 1000000, MAX_N);
    if (mode == 6) return rnd.next(1LL, MAX_N);
    if (mode == 7) {
        ll n = 1;
        int multipliers = rnd.next(1, 8);
        for (int i = 0; i < multipliers; ++i) {
            ll m = rnd.any(vector<ll>{2, 3, 5, 7, 11});
            if (n > MAX_N / m) break;
            n *= m;
        }
        return n;
    }
    return rnd.any(vector<ll>{1LL, 2LL, 3LL, 17LL, 999999999999999999LL, MAX_N});
}

pair<ll, ll> randomCosts() {
    int mode = rnd.next(0, 6);
    if (mode == 0) return {1, randomCost(3)};
    if (mode == 1) return {randomCost(3), 1};
    if (mode == 2) {
        ll x = randomCost(rnd.next(0, 3));
        return {x, x};
    }
    if (mode == 3) return {rnd.next(1, 10), rnd.next(MAX_COST - 1000, MAX_COST)};
    if (mode == 4) return {rnd.next(MAX_COST - 1000, MAX_COST), rnd.next(1, 10)};
    if (mode == 5) return {randomCost(0), randomCost(0)};
    return {randomCost(3), randomCost(3)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 30);
    if (rnd.next(0, 9) == 0) T = rnd.next(31, 100);

    vector<pair<ll, pair<ll, ll>>> cases;
    cases.reserve(T);

    vector<pair<ll, pair<ll, ll>>> anchors = {
        {1, {1, 1}},
        {2, {1, MAX_COST}},
        {17, {1, 5}},
        {MAX_N, {MAX_COST, MAX_COST}},
        {999999999999999999LL, {MAX_COST, 1}},
    };

    shuffle(anchors.begin(), anchors.end());
    for (const auto& tc : anchors) {
        if ((int)cases.size() < T && rnd.next(0, 1)) cases.push_back(tc);
    }

    while ((int)cases.size() < T) {
        ll n = randomN();
        auto costs = randomCosts();
        cases.push_back({n, costs});
    }

    shuffle(cases.begin(), cases.end());

    println(T);
    for (const auto& tc : cases) {
        println(tc.first);
        println(tc.second.first, tc.second.second);
    }

    return 0;
}
