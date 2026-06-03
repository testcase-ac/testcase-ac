#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

const ll MAX_VALUE = 1000000000000LL;

ll smallValue(ll hi) {
    return rnd.next(0LL, hi);
}

ll largeValue() {
    ll offset = rnd.next(0LL, 1000000LL);
    return MAX_VALUE - offset;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    ll a, b, c, d;
    vector<ll> x;

    if (mode == 0) {
        n = 1;
        a = smallValue(20);
        b = smallValue(20);
        c = rnd.next(1LL, 20LL);
        d = smallValue(20);
        x = {smallValue(20)};
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        a = smallValue(50);
        b = smallValue(50);
        c = 1;
        d = smallValue(50);
        x.assign(n, smallValue(50));
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        a = largeValue();
        b = largeValue();
        c = largeValue();
        d = largeValue();
        x.resize(n);
        for (ll& value : x) value = rnd.next(largeValue(), MAX_VALUE);
    } else if (mode == 3) {
        n = rnd.next(2, 14);
        a = rnd.next(0LL, MAX_VALUE);
        b = rnd.next(0LL, MAX_VALUE);
        c = rnd.next(1LL, MAX_VALUE);
        d = rnd.next(0LL, MAX_VALUE);
        ll value = rnd.next(0LL, MAX_VALUE);
        x.assign(n, value);
    } else if (mode == 4) {
        n = rnd.next(3, 15);
        a = smallValue(1000);
        b = smallValue(1000);
        c = rnd.next(1LL, 1000LL);
        d = smallValue(1000);
        x.resize(n);
        ll start = smallValue(1000);
        ll step = rnd.next(0LL, 100LL);
        for (int i = 0; i < n; ++i) x[i] = min(MAX_VALUE, start + step * i);
        if (rnd.next(0, 1)) reverse(x.begin(), x.end());
    } else if (mode == 5) {
        n = rnd.next(4, 16);
        a = rnd.any(vector<ll>{0, 1, rnd.next(0LL, 1000000LL), MAX_VALUE});
        b = rnd.any(vector<ll>{0, 1, rnd.next(0LL, 1000000LL), MAX_VALUE});
        c = rnd.any(vector<ll>{1, 2, rnd.next(1LL, 1000000LL), MAX_VALUE});
        d = rnd.any(vector<ll>{0, 1, rnd.next(0LL, 1000000LL), MAX_VALUE});
        vector<ll> pool = {0, 1, rnd.next(0LL, 1000000LL), largeValue(), MAX_VALUE};
        x.resize(n);
        for (ll& value : x) value = rnd.any(pool);
    } else {
        n = rnd.next(2, 18);
        a = rnd.next(0LL, MAX_VALUE);
        b = rnd.next(0LL, MAX_VALUE);
        c = rnd.next(1LL, MAX_VALUE);
        d = rnd.next(0LL, MAX_VALUE);
        x.resize(n);
        for (ll& value : x) value = rnd.next(0LL, MAX_VALUE);
    }

    println(n);
    println(a, b, c, d);
    println(x);

    return 0;
}
