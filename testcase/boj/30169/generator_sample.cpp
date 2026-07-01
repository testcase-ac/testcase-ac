#include "testlib.h"
#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

using int64 = long long;

int64 boundedPower(int base, int exp) {
    int64 value = 1;
    for (int i = 0; i < exp; ++i) value *= base;
    return value;
}

int64 randomNearPower(int base) {
    int exp = rnd.next(1, 18);
    int64 value = 1;
    for (int i = 0; i < exp && value <= 1000000000000000000LL / base; ++i) {
        value *= base;
    }

    int64 delta = rnd.next(-20, 20);
    if (delta < 0 && value <= -delta) return 1;
    value += delta;
    return min(1000000000000000000LL, max(1LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    const vector<int> largePrimes = {999999937, 999999929, 999999893, 999999883};

    int mode = rnd.next(0, 5);
    int64 x = 2;
    int64 n = 1;

    if (mode == 0) {
        x = rnd.next(2, 200);
        n = rnd.next(1, 1000);
    } else if (mode == 1) {
        x = rnd.any(smallPrimes);
        if (rnd.next(0, 1)) x = rnd.any(largePrimes);
        n = randomNearPower((int)min<int64>(x, 97));
    } else if (mode == 2) {
        int p = rnd.any(smallPrimes);
        int maxExp = 1;
        int64 value = p;
        while (value <= 1000000000LL / p) {
            value *= p;
            ++maxExp;
        }
        x = boundedPower(p, rnd.next(1, maxExp));
        n = randomNearPower(p);
    } else if (mode == 3) {
        vector<int> primes = smallPrimes;
        shuffle(primes.begin(), primes.end());
        x = 1;
        for (int p : primes) {
            int repeats = rnd.next(1, 3);
            for (int i = 0; i < repeats && x <= 1000000000LL / p; ++i) x *= p;
            if (x > 1 && rnd.next(0, 2) == 0) break;
        }
        n = rnd.next(1LL, 1000000000000LL);
    } else if (mode == 4) {
        x = rnd.next(900000000, 1000000000);
        n = rnd.next(999999999999000000LL, 1000000000000000000LL);
    } else {
        int a = rnd.any(smallPrimes);
        int b = rnd.any(smallPrimes);
        int c = rnd.any(smallPrimes);
        x = 1LL * a * b * c;
        if (rnd.next(0, 1) && x <= 1000000000LL / 99991) x *= 99991;
        n = rnd.next(1LL, 1000000000000000000LL);
    }

    println(x, n);
    return 0;
}
