#include "testlib.h"

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll MAXV = 3000000000LL;
    const ll POW31 = 2147483648LL;

    ll n = 1;
    ll m = 1;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = rnd.next(1LL, 80LL);
        m = 1;
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(1LL, 120LL);
    } else if (mode == 2) {
        n = rnd.next(1LL, 25LL);
        m = rnd.next(1LL, 25LL);
    } else if (mode == 3) {
        n = rnd.next(POW31 - 20, POW31 + 20);
        m = rnd.next(POW31 - 20, POW31 + 20);
    } else if (mode == 4) {
        n = rnd.next(MAXV - 1000, MAXV);
        m = rnd.next(1LL, 40LL);
    } else if (mode == 5) {
        n = rnd.next(1LL, 40LL);
        m = rnd.next(MAXV - 1000, MAXV);
    } else if (mode == 6) {
        n = rnd.next(MAXV - 1000, MAXV);
        m = rnd.next(MAXV - 1000, MAXV);
    } else {
        n = rnd.next(1LL, MAXV);
        m = rnd.next(1LL, MAXV);
    }

    println(n, m);
    return 0;
}
