#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_DIM = 2;
    const long long MAX_DIM = 2100000000LL;

    long long m = MIN_DIM;
    long long n = MIN_DIM;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        m = rnd.next(MIN_DIM, 30LL);
        n = rnd.next(MIN_DIM, 30LL);
    } else if (mode == 1) {
        m = 2;
        n = rnd.next(MIN_DIM, MAX_DIM);
    } else if (mode == 2) {
        m = rnd.next(MIN_DIM, MAX_DIM);
        n = 2;
    } else if (mode == 3) {
        long long base = rnd.next(MIN_DIM, 1000000LL);
        m = base;
        n = base + rnd.next(0LL, 3LL);
    } else if (mode == 4) {
        long long offsetM = rnd.next(0LL, 1000LL);
        long long offsetN = rnd.next(0LL, 1000LL);
        m = MAX_DIM - offsetM;
        n = MAX_DIM - offsetN;
    } else if (mode == 5) {
        long long k = rnd.next(1LL, 1000000000LL);
        m = 2 * k;
        n = rnd.next(MIN_DIM, 2100000LL);
    } else if (mode == 6) {
        long long k = rnd.next(1LL, 999999999LL);
        m = 2 * k + 1;
        n = rnd.next(MIN_DIM, 2100000LL);
    } else {
        m = rnd.next(MIN_DIM, MAX_DIM);
        n = rnd.next(MIN_DIM, MAX_DIM);
    }

    if (rnd.next(0, 1) == 1)
        std::swap(m, n);

    println(m, n);
    return 0;
}
