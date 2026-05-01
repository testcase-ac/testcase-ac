#include "testlib.h"
using namespace std;

long long modpow(long long a, long long e, long long mod) {
    long long r = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1)
            r = (long long)((__int128)r * a % mod);
        a = (long long)((__int128)a * a % mod);
        e >>= 1;
    }
    return r;
}

bool isPrime(long long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (long long i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long BIG_PRIME = 999999937LL;

    vector<long long> smallPrimes = {
        3,5,7,11,13,17,19,23,29,31,37,41,43,47,53
    };

    vector<long long> smallComposites = {
        4,6,8,9,10,12,14,15,16,18,21,22,24,25,26,27,28,30,33,34,35,36
    };

    // Known pseudoprimes for base 2 (all composite, satisfy a^p ≡ a mod p)
    vector<pair<long long,long long>> pseudoBase2 = {
        {341,2},{561,2},{645,2},{1729,2},{1905,2},
        {2047,2},{2465,2},{6601,2},{8911,2},{41041,2}
    };

    // Some Carmichael numbers (pseudoprime for all coprime bases)
    vector<long long> carmichael = {
        561,1105,1729,2465,2821,6601,8911,10585,41041
    };

    vector<pair<long long,long long>> tests;

    // Anchor 1: small prime (should be "no" even though Fermat holds)
    {
        long long p = rnd.any(smallPrimes);
        long long a = rnd.next(2LL, p - 1);
        tests.push_back({p, a});
    }

    // Anchor 2: large prime near upper bound
    {
        long long p = BIG_PRIME;
        long long a = rnd.next(2LL, p - 1);
        tests.push_back({p, a});
    }

    // Anchor 3: classic base-2 pseudoprime (composite, yes)
    {
        auto pa = rnd.any(pseudoBase2);
        tests.push_back(pa);
    }

    // Anchor 4: Carmichael number with some base (yes)
    {
        long long p = rnd.any(carmichael);
        long long a = rnd.next(2LL, p - 1);
        tests.push_back({p, a});
    }

    // Anchor 5: pseudoprime with gcd(p,a) > 1  -> catches solutions that require gcd(a,p)=1
    {
        long long p = 6;
        long long a = 3; // 3^6 ≡ 3 (mod 6)
        tests.push_back({p, a});
    }

    // Anchor 6: guaranteed composite "no" case
    {
        long long p = rnd.any(smallComposites);
        long long a;
        // Find an 'a' where Fermat equality does NOT hold
        for (int tries = 0; ; ++tries) {
            a = rnd.next(2LL, p - 1);
            bool cond = (!isPrime(p) && modpow(a, p, p) == a % p);
            if (!cond || tries > 100) break;
        }
        tests.push_back({p, a});
    }

    int minTotal = 8;
    int maxTotal = 18;
    int total = rnd.next(minTotal, maxTotal);
    int additional = max(0, total - (int)tests.size());

    for (int i = 0; i < additional; ++i) {
        int type = rnd.next(0, 4);
        long long p, a;
        if (type == 0) {
            // Random prime from small / big set
            if (rnd.next(0, 1) == 0)
                p = rnd.any(smallPrimes);
            else
                p = BIG_PRIME;
            a = rnd.next(2LL, p - 1);
        } else if (type == 1) {
            // Random small composite
            p = rnd.any(smallComposites);
            a = rnd.next(2LL, p - 1);
        } else if (type == 2) {
            // Another known base-2 pseudoprime
            auto pa = rnd.any(pseudoBase2);
            p = pa.first;
            a = pa.second;
        } else if (type == 3) {
            // Large random number (could be prime or composite)
            p = rnd.next(100000000LL, 1000000000LL);
            if (p <= 2) p = 3;
            a = rnd.next(2LL, p - 1);
        } else {
            // Random small p in [3, 50]
            p = rnd.next(3LL, 50LL);
            a = rnd.next(2LL, p - 1);
        }
        tests.push_back({p, a});
    }

    // Shuffle to mix anchors and random cases
    shuffle(tests.begin(), tests.end());

    for (auto &pa : tests) {
        println(pa.first, pa.second);
    }
    println(0, 0);

    return 0;
}
