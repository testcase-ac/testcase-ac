#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000LL;
    int mode = rnd.next(0, 7);

    long long l = 1;
    long long len = 1;
    long long k = 1;

    if (mode == 0) {
        l = rnd.next(1LL, LIMIT);
        len = 1;
        k = 1;
    } else if (mode == 1) {
        len = rnd.next(2LL, 10LL);
        l = rnd.next(1LL, LIMIT - len + 1);
        k = rnd.next(1LL, len);
    } else if (mode == 2) {
        len = rnd.next(2LL, 30LL);
        l = rnd.next(1LL, LIMIT - len + 1);
        k = min(len, rnd.next(1LL, 4LL));
    } else if (mode == 3) {
        len = rnd.next(4LL, 80LL);
        long long base = 1LL << rnd.next(2, 39);
        long long low = max(1LL, base - len / 2);
        long long high = min(LIMIT - len + 1, base + len / 2);
        if (low > high) {
            low = 1;
            high = LIMIT - len + 1;
        }
        l = rnd.next(low, high);
        k = rnd.next(1LL, min(len, 12LL));
    } else if (mode == 4) {
        len = rnd.next(2LL, 50LL);
        l = LIMIT - len + 1;
        k = rnd.next(1LL, len);
    } else if (mode == 5) {
        len = rnd.next(100LL, 1000LL);
        l = rnd.next(1LL, LIMIT - len + 1);
        k = rnd.next(max(1LL, len / 2), min(1000000LL, len));
    } else if (mode == 6) {
        len = rnd.next(1000000LL, 2000000LL);
        l = rnd.next(1LL, LIMIT - len + 1);
        k = rnd.next(999900LL, 1000000LL);
    } else {
        len = rnd.next(1LL, LIMIT);
        l = rnd.next(1LL, LIMIT - len + 1);
        k = rnd.next(1LL, min(1000000LL, len));
    }

    long long r = l + len - 1;
    println(l, r, k);

    return 0;
}
