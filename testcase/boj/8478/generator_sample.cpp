#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000000000LL;
    const int maxM = 1000000;

    int mode = rnd.next(0, 7);
    long long n;
    int m;

    if (mode == 0) {
        n = rnd.next(1LL, 12LL);
        m = rnd.next(1, 200);
    } else if (mode == 1) {
        m = rnd.next(1, 20);
        n = rnd.next(1LL, 200LL);
    } else if (mode == 2) {
        m = rnd.any(std::vector<int>{1, 2, 3, 4, 5, 10, 100, 1000, maxM});
        n = rnd.next(1LL, maxN);
    } else if (mode == 3) {
        m = rnd.next(1, maxM);
        long long period = 2LL * m;
        long long k = rnd.next(0LL, maxN / period);
        long long delta = rnd.next(0LL, period - 1);
        n = k * period + delta;
        if (n < 1) n = 1;
    } else if (mode == 4) {
        m = rnd.next(999000, maxM);
        n = rnd.next(maxN - 1000000LL, maxN);
    } else if (mode == 5) {
        m = rnd.next(1, maxM);
        long long period = 2LL * m;
        long long base = rnd.next(1LL, maxN / period) * period;
        long long offset = rnd.any(std::vector<long long>{-2, -1, 0, 1, 2});
        n = base + offset;
        if (n < 1) n = 1;
        if (n > maxN) n = maxN;
    } else if (mode == 6) {
        n = rnd.any(std::vector<long long>{1LL, 2LL, 3LL, 4LL, 5LL, 10LL, 100LL, maxN});
        m = rnd.next(1, maxM);
    } else {
        n = rnd.next(1LL, maxN);
        m = rnd.next(1, maxM);
    }

    println(n, m);
    return 0;
}
