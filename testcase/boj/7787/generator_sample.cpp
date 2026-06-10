#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAXV = 1000000000;

int clampValue(long long x) {
    if (x < 1) return 1;
    if (x > MAXV) return MAXV;
    return static_cast<int>(x);
}

int randomOdd(int lo, int hi) {
    lo = max(lo, 1);
    if (lo % 2 == 0) ++lo;
    if (hi % 2 == 0) --hi;
    return rnd.next((hi - lo) / 2 + 1) * 2 + lo;
}

int randomWithParity(int lo, int hi, int parity) {
    lo = max(lo, 1);
    if (lo % 2 != parity) ++lo;
    if (hi % 2 != parity) --hi;
    return rnd.next((hi - lo) / 2 + 1) * 2 + lo;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int r = 1;
    int g = 1;

    if (mode == 0) {
        int limit = rnd.next(3, 200);
        r = rnd.next(1, limit);
        g = rnd.next(1, limit);
    } else if (mode == 1) {
        int rParity = rnd.next(2);
        int gParity = 1 - rParity;
        r = randomWithParity(1, 999, rParity);
        g = randomWithParity(1, 999, gParity);
    } else if (mode == 2) {
        int parity = rnd.next(2);
        r = randomWithParity(1, 2000, parity);
        g = randomWithParity(1, 2000, parity);
    } else if (mode == 3) {
        int exp = rnd.next(0, 20);
        int base = 1 << exp;
        int odd1 = randomOdd(1, min(MAXV / base, 999));
        int odd2 = randomOdd(1, min(MAXV / base, 999));
        r = base * odd1;
        g = base * odd2;
    } else if (mode == 4) {
        int exp1 = rnd.next(0, 20);
        int exp2 = rnd.next(0, 20);
        int base1 = 1 << exp1;
        int base2 = 1 << exp2;
        r = base1 * randomOdd(1, min(MAXV / base1, 301));
        g = base2 * randomOdd(1, min(MAXV / base2, 301));
    } else if (mode == 5) {
        int exp = rnd.next(1, 29);
        long long power = 1LL << exp;
        r = clampValue(power + rnd.next(-3, 3));
        g = clampValue((1LL << rnd.next(0, 29)) + rnd.next(-3, 3));
    } else {
        vector<int> special = {1, 2, 3, 4, 5, 8, 16, 31, 32, 33, 999999937, MAXV};
        r = rnd.any(special);
        g = rnd.next(MAXV - 5000, MAXV);
    }

    if (rnd.next(2)) swap(r, g);
    println(r, g);
    return 0;
}
