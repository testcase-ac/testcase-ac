#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> smallPrimes = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    vector<int> mediumPrimes = {37, 41, 43, 47, 53, 59, 61, 67, 71, 73};
    vector<int> largePrimes = {1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049};

    vector<int> primes;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        primes = smallPrimes;
    } else if (mode == 1) {
        primes = mediumPrimes;
    } else if (mode == 2) {
        primes = largePrimes;
    } else {
        primes = smallPrimes;
        primes.insert(primes.end(), mediumPrimes.begin(), mediumPrimes.end());
        primes.insert(primes.end(), largePrimes.begin(), largePrimes.end());
    }

    int p = rnd.any(primes);
    int q = rnd.any(primes);
    while (q == p) {
        q = rnd.any(primes);
    }

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    vector<int> exponents;
    for (int e = 3; e < phi; e += 2) {
        if (gcd(e, phi) == 1) {
            exponents.push_back(e);
        }
    }

    int e = rnd.any(exponents);
    if (rnd.next(0, 3) == 0) {
        e = exponents.front();
    } else if (rnd.next(0, 3) == 0) {
        e = exponents.back();
    }

    int message = rnd.next(1, n - 1);
    int c = static_cast<int>(modPow(message, e, n));

    println(n, e, c);
    return 0;
}
