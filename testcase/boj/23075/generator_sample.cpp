#include "testlib.h"

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll maxN = 10000000000LL;
    ll n;

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        ll k = rnd.next(0, 30);
        n = 2 * k + rnd.next(0, 1);
        if (n < 1) n = 1;
    } else if (mode == 2) {
        ll base = rnd.next(1, 200);
        n = 6 * base + rnd.next(0, 5);
    } else if (mode == 3) {
        n = rnd.next(1LL, 1000000LL);
    } else if (mode == 4) {
        ll tail = rnd.next(0LL, 1000LL);
        n = maxN - tail;
    } else if (mode == 5) {
        ll base = rnd.next(1000000LL, 1666666666LL);
        n = 6 * base + rnd.next(0, 4);
        if (n > maxN) n = maxN;
    } else {
        n = rnd.next(1LL, maxN);
    }

    println(n);
    return 0;
}
