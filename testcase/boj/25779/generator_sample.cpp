#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_VALUE = 100000000000000000LL;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> smallPrimes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43
    };
    vector<long long> mediumPrimes = {
        101, 103, 107, 109, 113, 127, 131, 137, 139, 149
    };
    vector<long long> nearHundredMillionPrimes = {
        99999989LL, 99999931LL, 99999847LL, 99999839LL
    };
    vector<long long> billionPrimes = {
        1000000007LL, 1000000009LL, 1000000033LL
    };

    vector<long long> primes;
    long long n;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1LL, 80LL);
        int k = rnd.next(1, 6);
        shuffle(smallPrimes.begin(), smallPrimes.end());
        primes.assign(smallPrimes.begin(), smallPrimes.begin() + k);
    } else if (mode == 1) {
        n = rnd.next(1LL, 1000000LL);
        int k = rnd.next(7, 14);
        primes.assign(smallPrimes.begin(), smallPrimes.begin() + k);
        shuffle(primes.begin(), primes.end());
    } else if (mode == 2) {
        n = rnd.next(MAX_VALUE - 1000000LL, MAX_VALUE);
        int k = rnd.next(1, 4);
        primes.assign(smallPrimes.begin(), smallPrimes.begin() + k);
        shuffle(primes.begin(), primes.end());
    } else if (mode == 3) {
        n = rnd.next(1LL, MAX_VALUE);
        int k = rnd.next(2, 5);
        shuffle(mediumPrimes.begin(), mediumPrimes.end());
        primes.assign(mediumPrimes.begin(), mediumPrimes.begin() + k);
    } else if (mode == 4) {
        n = rnd.next(1LL, MAX_VALUE);
        primes = {
            rnd.any(nearHundredMillionPrimes),
            rnd.any(billionPrimes),
        };
        shuffle(primes.begin(), primes.end());
    } else {
        n = rnd.next(1LL, MAX_VALUE);
        vector<long long> pool = smallPrimes;
        pool.insert(pool.end(), mediumPrimes.begin(), mediumPrimes.end());
        pool.push_back(99999989LL);
        shuffle(pool.begin(), pool.end());

        __int128 product = 1;
        for (long long p : pool) {
            if (product * p > MAX_VALUE) {
                continue;
            }
            primes.push_back(p);
            product *= p;
            if ((int)primes.size() == 14 || rnd.next(0, 2) == 0) {
                break;
            }
        }
        if (primes.empty()) {
            primes.push_back(2);
        }
    }

    println(n, (int)primes.size());
    println(primes);
    return 0;
}
