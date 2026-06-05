#include "testlib.h"

long long clampN(long long n) {
    if (n < 1) return 1;
    if (n > 1000000000000000000LL) return 1000000000000000000LL;
    return n;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int m;
    long long n;

    if (mode == 0) {
        m = rnd.next(2, 10);
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        m = rnd.next(2, 100);
        n = rnd.next(1, m - 1);
    } else if (mode == 2) {
        m = rnd.next(2, 100);
        n = clampN((long long)m + rnd.next(-3, 3));
    } else if (mode == 3) {
        m = rnd.next(2, 20);
        n = rnd.next(21, 500);
    } else if (mode == 4) {
        m = rnd.next(80, 100);
        n = rnd.next(80, 300);
    } else if (mode == 5) {
        m = rnd.next(2, 100);
        long long base = 1LL << rnd.next(0, 60);
        n = clampN(base + rnd.next(-1000LL, 1000LL));
    } else {
        m = rnd.next(2, 100);
        n = rnd.next(999999999999000000LL, 1000000000000000000LL);
    }

    println(n, m);
    return 0;
}
