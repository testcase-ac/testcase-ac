#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000LL;
    long long a, r, n, mod;

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        a = rnd.next(1LL, 20LL);
        r = rnd.next(1LL, 20LL);
        n = rnd.next(1LL, 20LL);
        mod = rnd.next(1LL, 50LL);
    } else if (mode == 1) {
        mod = rnd.next(1LL, 12LL);
        a = rnd.next(1LL, 200LL);
        r = rnd.next(1LL, 200LL);
        n = rnd.next(1LL, 1000LL);
    } else if (mode == 2) {
        mod = rnd.next(2LL, 1000LL);
        a = rnd.next(1LL, 100000LL);
        r = mod * rnd.next(1LL, MAX_VALUE / mod);
        n = rnd.next(2LL, 1000000LL);
    } else if (mode == 3) {
        mod = rnd.next(2LL, 1000000LL);
        a = rnd.next(1LL, MAX_VALUE);
        r = rnd.next(1LL, 100LL) * mod + 1;
        if (r > MAX_VALUE) r = 1;
        n = rnd.next(1LL, MAX_VALUE);
    } else if (mode == 4) {
        a = rnd.next(MAX_VALUE - 100000LL, MAX_VALUE);
        r = rnd.next(MAX_VALUE - 100000LL, MAX_VALUE);
        n = rnd.next(MAX_VALUE - 100000LL, MAX_VALUE);
        mod = rnd.next(MAX_VALUE - 100000LL, MAX_VALUE);
    } else if (mode == 5) {
        a = rnd.next(1LL, MAX_VALUE);
        r = rnd.next(1LL, MAX_VALUE);
        n = rnd.next(1LL, 40LL);
        mod = rnd.next(1LL, MAX_VALUE);
    } else if (mode == 6) {
        a = rnd.next(1LL, 1000000LL);
        r = rnd.next(1LL, 1000000LL);
        n = (rnd.next(1LL, 500000000LL) * 2);
        mod = rnd.next(1LL, 1000000LL);
    } else {
        a = rnd.next(1LL, 1000000LL);
        r = rnd.next(1LL, 1000000LL);
        n = (rnd.next(1LL, 499999999LL) * 2) + 1;
        mod = rnd.next(1LL, 1000000LL);
    }

    println(a, r, n, mod);
    return 0;
}
