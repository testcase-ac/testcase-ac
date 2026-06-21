#include "testlib.h"

#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 100000000000000LL;
    const int maxH = 10000000;

    int mode = rnd.next(0, 7);
    long long n;
    int a, b;

    if (mode == 0) {
        a = rnd.next(2, 20);
        b = a;
        n = rnd.next(5LL, 200LL);
    } else if (mode == 1) {
        a = rnd.next(2, 1000);
        b = a * rnd.next(2, max(2, min(maxH / a, 1000)));
        n = rnd.next(5LL, 100000LL);
    } else if (mode == 2) {
        do {
            a = rnd.next(2, 5000);
            b = rnd.next(2, 5000);
        } while (__gcd(a, b) != 1);
        n = rnd.next(5LL, 1000000LL);
    } else if (mode == 3) {
        int g = rnd.next(2, 1000);
        a = g * rnd.next(1, min(maxH / g, 300));
        b = g * rnd.next(1, min(maxH / g, 300));
        if (a < 2) a = 2;
        if (b < 2) b = 2;
        n = rnd.next(5LL, 1000000LL);
    } else if (mode == 4) {
        a = rnd.next(maxH - 1000, maxH);
        b = rnd.next(maxH - 1000, maxH);
        n = rnd.next(5LL, 2LL * maxH);
    } else if (mode == 5) {
        a = rnd.next(2, 50);
        b = rnd.next(maxH - 1000, maxH);
        n = rnd.next(5LL, maxN);
    } else if (mode == 6) {
        a = rnd.next(2, maxH);
        b = rnd.next(2, maxH);
        long long around = 1LL * a * rnd.next(1, 1000) + 1LL * b * rnd.next(1, 1000);
        n = max(5LL, min(maxN, around + rnd.next(-20LL, 20LL)));
    } else {
        a = rnd.next(2, maxH);
        b = rnd.next(2, maxH);
        n = rnd.next(maxN - 1000000LL, maxN);
    }

    if (rnd.next(0, 1)) swap(a, b);
    println(n, a, b);
    return 0;
}
