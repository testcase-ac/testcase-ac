#include "testlib.h"
#include <vector>

using namespace std;

long long pickValue(int mode) {
    if (mode == 0) return rnd.next(1, 5);
    if (mode == 1) return rnd.next(1, 1000);
    if (mode == 2) return rnd.next(999999900, 1000000000);
    return rnd.next(1, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long n;

    if (mode == 0) {
        n = rnd.next(4, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 40);
    } else if (mode == 2) {
        vector<long long> interesting = {
            1000000LL,
            1000000000LL,
            1000000000000LL,
            1000000000000000000LL
        };
        n = rnd.any(interesting) - rnd.next(0, 20);
        if (n < 4) n = 4;
    } else if (mode == 3) {
        n = rnd.next(4LL, 1000000000000000000LL);
    } else {
        long long base = rnd.next(4LL, 2000000LL);
        int shift = rnd.next(0, 59);
        long long cap = 1000000000000000000LL;
        while (shift > 0 && base <= cap / 2) {
            base *= 2;
            --shift;
        }
        n = base;
    }

    int valueMode = rnd.next(0, 3);
    long long f1 = pickValue(valueMode);
    long long f2 = pickValue(rnd.next(0, 3));
    long long f3 = pickValue(rnd.next(0, 3));
    long long c = pickValue(rnd.next(0, 3));

    if (rnd.next(0, 9) == 0) {
        f1 = f2 = f3 = c = rnd.next(1, 20);
    }

    println(n, f1, f2, f3, c);
    return 0;
}
