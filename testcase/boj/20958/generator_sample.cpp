#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int productWithinLimit(const vector<int>& primes, int maxFactor, int rounds) {
    int value = 1;
    for (int round = 0; round < rounds; ++round) {
        int p = rnd.any(primes);
        if (value > maxFactor / p) break;
        value *= p;
    }
    return value;
}

int reducibleValue(const vector<int>& primes) {
    int factor = productWithinLimit(primes, 10000000 / 7, rnd.next(0, 6));
    return 7 * factor;
}

int impossibleValue(const vector<int>& primes) {
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        return 49 * rnd.next(1, 10000000 / 49);
    }
    if (mode == 1) {
        int value = rnd.next(1, 10000000);
        if (value % 7 == 0) ++value;
        return min(value, 10000000);
    }
    return productWithinLimit(primes, 10000000, rnd.next(1, 7));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 11, 13, 17, 19, 23, 29, 31};

    int n = rnd.next(1, 30);
    int m = rnd.next(1, n);
    int mode = rnd.next(0, 4);
    vector<int> s(n);

    if (mode == 0) {
        fill(s.begin(), s.end(), 7);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) s[i] = reducibleValue(primes);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            s[i] = (rnd.next(0, 4) == 0) ? 7 : reducibleValue(primes);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) s[i] = reducibleValue(primes);
        s[rnd.next(n)] = impossibleValue(primes);
    } else {
        for (int i = 0; i < n; ++i) {
            s[i] = (rnd.next(0, 1) == 0) ? reducibleValue(primes) : impossibleValue(primes);
        }
    }

    println(n, m);
    println(s);
    return 0;
}
