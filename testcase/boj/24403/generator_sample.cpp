#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

const ll MAX_N = 1000000000000000000LL;

ll clampN(ll n) {
    return max(2LL, min(MAX_N, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    vector<ll> primorials;
    ll product = 1;
    for (ll p : primes) {
        if (product > MAX_N / p) break;
        product *= p;
        primorials.push_back(product);
    }

    int mode = rnd.next(0, 6);
    ll n;

    if (mode == 0) {
        n = rnd.next(2LL, 200LL);
    } else if (mode == 1) {
        ll base = rnd.any(primorials);
        ll delta = rnd.next(-20LL, 20LL);
        n = clampN(base + delta);
    } else if (mode == 2) {
        ll base = rnd.any(primorials);
        ll multiplier = rnd.next(1LL, max(1LL, min(1000LL, MAX_N / base)));
        n = base * multiplier;
    } else if (mode == 3) {
        ll value = 1;
        ll factor = rnd.any(vector<ll>{2, 3, 5, 7, 10});
        int steps = rnd.next(1, 60);
        for (int i = 0; i < steps && value <= MAX_N / factor; ++i) {
            value *= factor;
        }
        n = value + rnd.next(0LL, min(1000LL, MAX_N - value));
    } else if (mode == 4) {
        ll tail = rnd.next(0LL, 1000000LL);
        n = MAX_N - tail;
    } else if (mode == 5) {
        ll hi = rnd.next(1000000000LL, MAX_N);
        ll lo = rnd.next(2LL, hi);
        n = rnd.next(lo, hi);
    } else {
        ll base = rnd.next(2LL, 1000000000LL);
        ll multiplier = rnd.next(1LL, MAX_N / base);
        n = base * multiplier + rnd.next(0LL, min(1000LL, MAX_N - base * multiplier));
    }

    println(clampN(n));
    return 0;
}
