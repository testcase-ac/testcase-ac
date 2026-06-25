#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long product(const vector<int>& factors) {
    long long result = 1;
    for (int factor : factors) result *= factor;
    return result;
}

vector<int> randomFactors(const vector<int>& primes, int count) {
    vector<int> pool = primes;
    shuffle(pool.begin(), pool.end());
    pool.resize(count);
    return pool;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
        41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    const vector<long long> largePrimes = {
        999983LL, 1000003LL, 1000033LL, 1000037LL, 999999996989LL,
        999999997063LL
    };
    const vector<long long> mediumPrimes = {
        999983LL, 1000003LL, 1000033LL, 1000037LL
    };

    long long a = 2;
    long long b = 3;
    int mode = rnd.next(0, 8);

    if (mode == 0) {
        a = rnd.any(largePrimes);
        do {
            b = rnd.any(largePrimes);
        } while (b == a);
    } else if (mode <= 2) {
        vector<int> factors = randomFactors(smallPrimes, rnd.next(3, 7));
        int split = rnd.next(1, static_cast<int>(factors.size()) - 1);
        a = product(vector<int>(factors.begin(), factors.begin() + split));
        b = product(vector<int>(factors.begin() + split, factors.end()));
        if (a < 2 || b < 2 || (a == 2 && b == 3)) {
            a *= rnd.any(smallPrimes);
        }
    } else if (mode <= 4) {
        long long p = rnd.any(smallPrimes);
        long long multiplier = rnd.any(smallPrimes);
        a = p * p * multiplier;
        b = rnd.any(largePrimes);
    } else if (mode <= 6) {
        long long p = rnd.any(smallPrimes);
        a = p * rnd.any(mediumPrimes);
        b = p * rnd.any(smallPrimes);
        if (b == p * p) b = p * 101;
    } else {
        long long p = rnd.any(largePrimes);
        a = p;
        b = p;
    }

    if (rnd.next(2)) swap(a, b);
    println(a, b);
    return 0;
}
