#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

using ll = long long;

static constexpr ll kMaxPile = 1000000000LL;

array<ll, 3> shuffledTriple(ll a, ll b, ll c) {
    array<ll, 3> values = {a, b, c};
    shuffle(values.begin(), values.end());
    return values;
}

ll randomPileNear(ll center, ll radius) {
    ll lo = max(1LL, center - radius);
    ll hi = min(kMaxPile, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(18, 45);
    vector<array<ll, 3>> cases;
    cases.reserve(T);

    while ((int)cases.size() < T) {
        int mode = rnd.next(0, 6);

        if (mode == 0) {
            ll x = rnd.next(1, 12);
            ll y = rnd.next(1, 12);
            ll z = rnd.next(1, 12);
            cases.push_back(shuffledTriple(x, y, z));
        } else if (mode == 1) {
            ll base = rnd.next(1, 500000000);
            ll x = base * 2 - rnd.next(0, 1);
            ll y = rnd.next(1, 500000000) * 2 - rnd.next(0, 1);
            ll z = rnd.next(1, 500000000) * 2 - rnd.next(0, 1);
            cases.push_back(shuffledTriple(x, y, z));
        } else if (mode == 2) {
            ll center = rnd.next(1LL, kMaxPile);
            cases.push_back(shuffledTriple(
                randomPileNear(center, 3),
                randomPileNear(center, 3),
                randomPileNear(center, 3)));
        } else if (mode == 3) {
            ll small = rnd.next(1, 5);
            ll large1 = rnd.next(kMaxPile - 20, kMaxPile);
            ll large2 = rnd.next(kMaxPile - 20, kMaxPile);
            cases.push_back(shuffledTriple(small, large1, large2));
        } else if (mode == 4) {
            ll a = rnd.next(1LL, kMaxPile);
            cases.push_back(shuffledTriple(a, a, rnd.next(1LL, kMaxPile)));
        } else if (mode == 5) {
            vector<ll> boundary = {
                1, 2, 3, 4, 5,
                kMaxPile - 4, kMaxPile - 3, kMaxPile - 2, kMaxPile - 1, kMaxPile
            };
            cases.push_back(shuffledTriple(
                rnd.any(boundary),
                rnd.any(boundary),
                rnd.any(boundary)));
        } else {
            ll a = rnd.next(1LL, kMaxPile);
            ll b = rnd.next(1LL, kMaxPile);
            ll c = rnd.next(1LL, kMaxPile);
            cases.push_back(shuffledTriple(a, b, c));
        }
    }

    println((int)cases.size());
    for (const auto& tc : cases) {
        println(tc[0], tc[1], tc[2]);
    }

    return 0;
}
