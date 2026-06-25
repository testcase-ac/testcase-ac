#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 10000000000000000LL;
    long long n;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        long long side = rnd.next(1LL, 100000000LL);
        long long area = side * side;
        long long gap = rnd.next(0LL, min(200LL, area - 1));
        n = area - gap;
    } else if (mode == 2) {
        long long h = rnd.next(1LL, 70000000LL);
        long long area = 2 * h * h;
        long long gap = rnd.next(0LL, min(500LL, area - 1));
        n = area - gap;
    } else if (mode == 3) {
        long long h = rnd.next(1LL, 70000000LL);
        long long w = rnd.next(h, min(2 * h, 142000000LL));
        long long area = h * w;
        long long gap = rnd.next(0LL, min(1000LL, area - 1));
        n = area - gap;
    } else if (mode == 4) {
        long long root = rnd.next(1LL, 100000000LL);
        long long offset = rnd.next(-1000LL, 1000LL);
        n = root * root + offset;
    } else if (mode == 5) {
        n = LIM - rnd.next(0LL, 1000000LL);
    } else if (mode == 6) {
        long long base = rnd.next(1LL, 100000000LL);
        long long mult = rnd.next(1LL, 100000000LL);
        n = base * mult;
    } else {
        n = rnd.next(1LL, LIM);
    }

    n = max(1LL, min(LIM, n));
    println(n);
    return 0;
}
