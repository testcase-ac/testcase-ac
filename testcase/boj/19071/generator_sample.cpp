#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    long long n;
    long long m;

    if (mode == 0) {
        n = rnd.next(1LL, 12LL);
        m = rnd.next(1LL, 30LL);
    } else if (mode == 1) {
        n = rnd.next(2LL, 40LL);
        m = rnd.next(1LL, max(1LL, n - 2));
    } else if (mode == 2) {
        n = rnd.next(2LL, 100LL);
        long long base = n - 1;
        long long delta = rnd.next(-2LL, 5LL);
        m = max(1LL, base + delta);
    } else if (mode == 3) {
        n = rnd.next(2LL, 300LL);
        long long complete = n * (n - 1) / 2;
        long long delta = rnd.next(-10LL, 10LL);
        m = max(1LL, complete + delta);
    } else if (mode == 4) {
        n = rnd.next(500LL, 1000000LL);
        long long span = min(1000000LL, n * 4);
        m = rnd.next(1LL, span);
    } else if (mode == 5) {
        n = rnd.next(1000LL, 1000000LL);
        long long complete = min(1000000000000LL, n * (n - 1) / 2);
        long long low = max(1LL, complete - 1000000LL);
        m = rnd.next(low, complete);
    } else {
        n = rnd.next(1LL, 1000000LL);
        m = rnd.next(999000000000LL, 1000000000000LL);
    }

    println(n, m);
    return 0;
}
