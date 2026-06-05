#include "testlib.h"
#include <vector>

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll MAX_N = 1000000000000000000LL;
    int mode = rnd.next(0, 5);
    ll n;

    if (mode == 0) {
        n = rnd.next(1LL, 20LL);
    } else if (mode == 1) {
        ll base = rnd.next(1LL, 500000000LL);
        n = 2LL * base + rnd.next(0, 1);
    } else if (mode == 2) {
        n = MAX_N - rnd.next(0LL, 1000LL);
    } else if (mode == 3) {
        n = rnd.next(1LL, MAX_N);
    } else if (mode == 4) {
        int exponent = rnd.next(0, 59);
        ll center = 1LL << exponent;
        ll delta = rnd.next(-5LL, 5LL);
        n = center + delta;
        if (n < 1) n = 1;
        if (n > MAX_N) n = MAX_N;
    } else {
        std::vector<ll> boundaryValues = {1LL, 2LL, 3LL, 8LL, 999999999999999999LL, MAX_N};
        n = rnd.any(boundaryValues);
    }

    println(n);
    return 0;
}
