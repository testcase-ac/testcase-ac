#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000LL;

    vector<long long> powers;
    long long p = 1;
    while (p <= LIMIT) {
        powers.push_back(p);
        if (p > LIMIT / 10) break;
        p *= 10;
    }

    long long n;
    int mode = rnd.next(7);
    if (mode == 0) {
        n = rnd.next(1LL, 120LL);
    } else if (mode == 1) {
        long long base = rnd.any(powers);
        long long delta = rnd.next(-25LL, 25LL);
        n = base + delta;
    } else if (mode == 2) {
        long long base = rnd.any(powers);
        n = base - rnd.next(1LL, min(25LL, base));
    } else if (mode == 3) {
        int digits = rnd.next(1, 12);
        n = 0;
        for (int i = 0; i < digits; ++i) n = n * 10 + rnd.any(string("13579"));
    } else if (mode == 4) {
        int digits = rnd.next(2, 12);
        n = rnd.next(1LL, 9LL);
        for (int i = 1; i < digits; ++i) n = n * 10 + rnd.next(0LL, 1LL) * 9;
    } else if (mode == 5) {
        n = rnd.next(1000LL, 1000000LL);
    } else {
        n = LIMIT - rnd.next(0LL, 1000000LL);
    }

    n = max(1LL, min(LIMIT, n));
    println(n);

    return 0;
}
