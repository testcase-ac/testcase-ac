#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using int64 = long long;

const int LIMIT = 1000000000;

int64 powLimited(int base, int exp) {
    int64 value = 1;
    for (int i = 0; i < exp; i++) {
        value *= base;
        if (value > LIMIT) return LIMIT + 1LL;
    }
    return value;
}

int maxPowerExp(int base) {
    int exp = 0;
    int64 value = 1;
    while (value * base <= LIMIT) {
        value *= base;
        exp++;
    }
    return exp;
}

int randomPrime() {
    const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    return rnd.any(primes);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int64 n = 1;
    int64 m = 1;

    if (mode == 0) {
        n = rnd.next(1, LIMIT);
        m = n;
    } else if (mode == 1) {
        int p = randomPrime();
        int q = randomPrime();
        while (q == p) q = randomPrime();

        int64 pPower = powLimited(p, rnd.next(1, 6));
        int64 qPower = powLimited(q, rnd.next(1, 6));
        n = pPower;
        m = qPower;
    } else if (mode == 2) {
        int p = randomPrime();
        int highExp = rnd.next(2, maxPowerExp(p));
        int lowExp = rnd.next(0, highExp - 1);
        n = powLimited(p, highExp);
        m = powLimited(p, lowExp);
    } else if (mode == 3) {
        int p = rnd.any(vector<int>{2, 3, 5, 7, 11, 13});
        int squares = rnd.next(1, 3);
        int maxStartExp = maxPowerExp(p) >> squares;
        if (maxStartExp < 1) {
            p = 2;
            maxStartExp = maxPowerExp(p) >> squares;
        }
        int startExp = rnd.next(1, maxStartExp);
        int endExp = startExp;
        for (int i = 0; i < squares; i++) endExp *= 2;

        n = powLimited(p, startExp);
        m = powLimited(p, endExp);
    } else if (mode == 4) {
        vector<int> primes = {2, 3, 5, 7, 11, 13};
        shuffle(primes.begin(), primes.end());

        int count = rnd.next(2, 4);
        for (int i = 0; i < count; i++) {
            int fromExp = rnd.next(1, 5);
            int toExp = rnd.next(0, fromExp * 2);
            int64 fromPower = powLimited(primes[i], fromExp);
            int64 toPower = powLimited(primes[i], toExp);

            if (n * fromPower > LIMIT || m * toPower > LIMIT) break;
            n *= fromPower;
            m *= toPower;
        }
    } else {
        const vector<int> values = {
            1,
            2,
            3,
            999999937,
            999999998,
            999999999,
            1000000000
        };
        n = rnd.any(values);
        m = rnd.any(values);
    }

    n = max<int64>(1, min<int64>(LIMIT, n));
    m = max<int64>(1, min<int64>(LIMIT, m));
    println(n, m);
    return 0;
}
