#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

using ll = long long;

const ll MAX_D = 1000000000LL;

array<ll, 3> shuffledTriple(ll a, ll b, ll c) {
    vector<ll> values = {a, b, c};
    shuffle(values.begin(), values.end());
    return {values[0], values[1], values[2]};
}

array<ll, 3> validTriple() {
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        ll x = rnd.next(0LL, 40LL);
        ll y = rnd.next(0LL, 40LL);
        ll z = rnd.next(0LL, 40LL);
        if (x + y == 0) y = 1;
        if (x + z == 0) z = 1;
        if (y + z == 0) z = 1;
        return shuffledTriple(y + z, x + z, x + y);
    }

    if (mode == 1) {
        ll sum = rnd.next(MAX_D - 1000, MAX_D);
        ll x = rnd.next(1LL, sum - 2);
        ll y = rnd.next(1LL, sum - x - 1);
        ll z = sum - x - y;
        return shuffledTriple(y + z, x + z, x + y);
    }

    if (mode == 2) {
        ll a = rnd.next(1LL, MAX_D / 2);
        ll b = rnd.next(1LL, MAX_D - a);
        return shuffledTriple(a, b, a + b);
    }

    if (mode == 3) {
        ll base = rnd.next(1LL, MAX_D / 2);
        return shuffledTriple(base, base, 2LL * base);
    }

    ll perimeterHalf = rnd.next(3LL, MAX_D);
    ll x = rnd.next(1LL, perimeterHalf - 2);
    ll y = rnd.next(1LL, perimeterHalf - x - 1);
    ll z = perimeterHalf - x - y;
    ll a = y + z;
    ll b = x + z;
    ll c = x + y;
    return shuffledTriple(a, b, c);
}

array<ll, 3> triangleFailure() {
    ll a = rnd.next(1LL, 2000LL);
    ll b = rnd.next(1LL, 2000LL);
    ll c = min(MAX_D, a + b + rnd.next(1LL, 2000LL));
    return shuffledTriple(a, b, c);
}

array<ll, 3> parityFailure() {
    auto t = validTriple();
    int idx = rnd.next(0, 2);
    if (t[idx] < MAX_D) {
        ++t[idx];
    } else {
        --t[idx];
    }
    return t;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    println(t);

    vector<array<ll, 3>> cases;
    cases.push_back(shuffledTriple(1, 1, 1));
    cases.push_back(shuffledTriple(1, 2, 3));
    cases.push_back(shuffledTriple(1, 1, 10));
    cases.push_back(shuffledTriple(MAX_D, MAX_D, MAX_D));

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 99);
        if (mode < 55) {
            cases.push_back(validTriple());
        } else if (mode < 80) {
            cases.push_back(triangleFailure());
        } else {
            cases.push_back(parityFailure());
        }
    }

    shuffle(cases.begin(), cases.end());
    for (auto [a, b, c] : cases) {
        println(a, b, c);
    }

    return 0;
}
