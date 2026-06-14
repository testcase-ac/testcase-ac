#include "testlib.h"

using ll = long long;

const int MAX_N = 500000;
const ll MAX_V = 1000000000000000000LL;

ll randValue() {
    int mode = rnd.next(6);
    if (mode == 0) return 0;
    if (mode == 1) return 1;
    if (mode == 2) return rnd.next(0LL, 1000LL);
    if (mode == 3) return rnd.next(0LL, 1000000000LL);
    if (mode == 4) return MAX_V - rnd.next(0LL, 1000LL);
    return rnd.next(0LL, MAX_V);
}

int randN() {
    int mode = rnd.next(5);
    if (mode == 0) return 1;
    if (mode == 1) return MAX_N;
    if (mode == 2) return rnd.next(2, 20);
    if (mode == 3) return rnd.next(21, 1000);
    return rnd.next(1, MAX_N);
}

ll cappedProduct(ll x, int y) {
    __int128 value = (__int128)x * y;
    return value > MAX_V ? MAX_V : (ll)value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = randN();
    ll l = 0;
    ll r = 0;
    ll a = 0;

    if (mode == 0) {
        l = 0;
        r = MAX_V;
        a = randValue();
    } else if (mode == 1) {
        l = randValue();
        r = l;
        int width = rnd.next(1, n);
        a = cappedProduct(l, width);
    } else if (mode == 2) {
        l = rnd.next(0LL, 1000000LL);
        r = rnd.next(l, 1000000000LL);
        int width = rnd.next(1, n);
        ll h = rnd.next(l, r);
        a = h * (ll)width;
        if (h != 0 && a / h != width) a = MAX_V;
    } else if (mode == 3) {
        l = rnd.next(1LL, 1000000LL);
        r = rnd.next(l, 1000000000LL);
        a = rnd.next(0LL, l * (ll)n - 1);
    } else if (mode == 4) {
        l = rnd.next(0LL, 1000000LL);
        r = rnd.next(l, 1000000000LL);
        a = MAX_V - rnd.next(0LL, 1000LL);
    } else if (mode == 5) {
        n = rnd.next(1, 30);
        l = rnd.next(0LL, 20LL);
        r = rnd.next(l, 40LL);
        a = rnd.next(0LL, 200LL);
    } else if (mode == 6) {
        l = randValue();
        r = rnd.next(l, MAX_V);
        a = cappedProduct(l, n);
    } else {
        l = randValue();
        r = rnd.next(l, MAX_V);
        a = rnd.next(0LL, MAX_V);
    }

    println(n, a, l, r);
    return 0;
}
