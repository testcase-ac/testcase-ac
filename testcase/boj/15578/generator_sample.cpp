#include "testlib.h"

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    ll k, m;

    if (mode == 0) {
        n = rnd.next(2, 12);
        k = rnd.next(1LL, 20LL);
        m = rnd.next(k, 4LL * n * k);
    } else if (mode == 1) {
        n = rnd.next(2, 60);
        k = rnd.next(1LL, 10000LL);
        ll period = 2LL * (n - 1) * k;
        ll cycles = rnd.next(1LL, 2000000000LL / period);
        ll rem = rnd.next(0LL, period - 1);
        m = period * cycles + rem;
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        k = rnd.next(2LL, 1000000LL);
        ll visits = rnd.next(1LL, 2LL * n - 2);
        ll partial = rnd.next(1LL, k - 1);
        m = visits * k + partial;
        if (m > 2000000000LL) {
            m = rnd.next(k, 2000000000LL);
        }
    } else if (mode == 3) {
        n = rnd.next(100000, 200000);
        k = rnd.next(1LL, 2000000000LL);
        m = rnd.next(k, 2000000000LL);
    } else {
        n = rnd.next(2, 200000);
        k = rnd.next(1LL, 2000000000LL);
        m = k;
    }

    println(n, k, m);
    return 0;
}
