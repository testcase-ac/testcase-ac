#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000000LL;
    int mode = rnd.next(0, 7);
    long long n;

    if (mode == 0) {
        n = rnd.next(0LL, 30LL);
    } else if (mode == 1) {
        n = rnd.next(31LL, 1000LL);
    } else if (mode == 2) {
        n = rnd.next(1001LL, 1000000LL);
    } else if (mode == 3) {
        n = rnd.next(1000000LL, 1000000000LL);
    } else if (mode == 4) {
        n = rnd.next(1000000000LL, maxN);
    } else if (mode == 5) {
        long long base = 1LL;
        int exponent = rnd.next(0, 15);
        for (int i = 0; i < exponent; ++i) base *= 10LL;
        n = base + rnd.next(-20LL, 20LL);
        if (n < 0) n = 0;
        if (n > maxN) n = maxN;
    } else if (mode == 6) {
        long long fib[80];
        fib[0] = fib[1] = 1;
        int last = 1;
        while (last + 1 < 80 && fib[last] <= maxN - fib[last - 1]) {
            ++last;
            fib[last] = fib[last - 1] + fib[last - 2];
        }
        int idx = rnd.next(1, last);
        n = fib[idx] + rnd.next(-10LL, 10LL);
        if (n < 0) n = 0;
        if (n > maxN) n = maxN;
    } else {
        n = maxN - rnd.next(0LL, 1000000LL);
    }

    println(n);
    return 0;
}
