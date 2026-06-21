#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n = rnd.next(1, 18);
    if (rnd.next(0, 9) == 0) n = rnd.next(19, 80);

    vector<ll> h(n);

    if (mode == 0) {
        ll start = rnd.next(1LL, 1000LL);
        ll step = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) h[i] = min(1000000000LL, start + step * i);
    } else if (mode == 1) {
        ll start = rnd.next(1LL, 1000LL);
        ll step = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) h[i] = min(1000000000LL, start + step * (n - 1 - i));
    } else if (mode == 2) {
        ll base = rnd.next(1LL, 1000LL);
        ll linear = rnd.next(0LL, 10LL);
        ll curve = rnd.next(1LL, 5LL);
        for (int i = 0; i < n; ++i) {
            h[i] = min(1000000000LL, base + linear * i + curve * i * i);
        }
    } else if (mode == 3) {
        ll top = rnd.next(1000LL, 1000000LL);
        ll linear = rnd.next(0LL, 10LL);
        ll curve = rnd.next(1LL, 5LL);
        for (int i = 0; i < n; ++i) {
            ll drop = linear * i + curve * i * i;
            h[i] = max(1LL, top - drop);
        }
    } else if (mode == 4) {
        ll low = rnd.next(1LL, 100LL);
        ll high = rnd.next(1000000LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            h[i] = (i % 2 == 0) ? high - rnd.next(0LL, 1000LL) : low + rnd.next(0LL, 1000LL);
            h[i] = max(1LL, min(1000000000LL, h[i]));
        }
    } else if (mode == 5) {
        ll base = rnd.next(1LL, 1000000LL);
        for (int i = 0; i < n; ++i) {
            h[i] = base + rnd.next(0LL, 3LL);
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            h[i] = rnd.next(0, 1) ? rnd.next(1LL, 20LL) : rnd.next(999999980LL, 1000000000LL);
        }
    } else if (mode == 7) {
        for (int i = 0; i < n; ++i) h[i] = rnd.next(1LL, 1000LL);
        if (n >= 3) h[rnd.next(1, n - 2)] = rnd.next(999999000LL, 1000000000LL);
    } else {
        n = rnd.next(1, 2000);
        h.assign(n, 1);
        int blocks = rnd.next(1, min(n, 20));
        for (int b = 0; b < blocks; ++b) {
            ll value = rnd.next(1LL, 1000000000LL);
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, n - 1);
            for (int i = l; i <= r; ++i) h[i] = value;
        }
    }

    println(n);
    println(h);

    return 0;
}
