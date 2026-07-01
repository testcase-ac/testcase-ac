#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_VALUE = 100000000000000000LL;

long long mulMod(long long a, long long b, long long mod) {
    return (long long)((__int128)a * b % mod);
}

long long powMod(long long a, long long e, long long mod) {
    long long result = 1 % mod;
    while (e > 0) {
        if (e & 1) {
            result = mulMod(result, a, mod);
        }
        a = mulMod(a, a, mod);
        e >>= 1;
    }
    return result;
}

bool isPrime(long long n) {
    if (n < 2) {
        return false;
    }
    for (long long p : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
        if (n == p) {
            return true;
        }
        if (n % p == 0) {
            return false;
        }
    }

    long long d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    for (long long a : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
        if (a >= n) {
            continue;
        }
        long long x = powMod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mulMod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, MAX_VALUE, "n");
    inf.readSpace();
    int k = inf.readInt(1, 14, "k");
    inf.readEoln();

    vector<long long> primes;
    __int128 product = 1;
    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        long long p = inf.readLong(2LL, MAX_VALUE, "p_i");
        ensuref(isPrime(p), "p_%d must be prime: %lld", i + 1, p);
        ensuref(find(primes.begin(), primes.end(), p) == primes.end(),
                "p_%d is duplicated: %lld", i + 1, p);
        product *= p;
        ensuref(product <= MAX_VALUE, "product of primes exceeds 10^17");
        primes.push_back(p);
    }
    inf.readEoln();
    inf.readEof();
}
