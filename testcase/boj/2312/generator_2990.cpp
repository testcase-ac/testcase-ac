#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int MAXN = 100000;

    // Sieve to build primes up to MAXN
    vector<bool> isPrime(MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    vector<int> primes;
    for (int i = 2; i <= MAXN; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
            if ((long long)i * i <= MAXN) {
                for (int j = i * i; j <= MAXN; j += i)
                    isPrime[j] = false;
            }
        }
    }

    // Prepare small primes for exponentiation and product cases
    vector<int> primesExp, primesProd, largePrimes;
    for (int p : primes) {
        if (p <= 100) primesExp.push_back(p);
        if (p <= 1000) primesProd.push_back(p);
    }
    // Take a handful of the largest primes for prime-case
    int K = 20;
    int P = primes.size();
    for (int i = max(0, P - K); i < P; ++i)
        largePrimes.push_back(primes[i]);

    // Number of test cases
    int T = rnd.next(1, 10);
    vector<int> tests;
    tests.reserve(T);

    for (int i = 0; i < T; ++i) {
        int typ = rnd.next(0, 4);
        int n = 2;
        if (typ == 0) {
            // Small random N
            n = rnd.next(2, 50);
        } else if (typ == 1) {
            // Large random N
            n = rnd.next(50000, MAXN);
        } else if (typ == 2) {
            // A large prime
            n = rnd.any(largePrimes);
        } else if (typ == 3) {
            // Prime power p^e
            int p = rnd.any(primesExp);
            int maxE = 1;
            long long v = p;
            while (v * p <= MAXN) {
                v *= p;
                maxE++;
            }
            int e = rnd.next(2, maxE);
            long long val = 1;
            for (int j = 0; j < e; ++j) val *= p;
            n = (int)val;
        } else {
            // Product of two primes
            int p, q;
            long long prod;
            do {
                p = rnd.any(primesProd);
                q = rnd.any(primesProd);
                prod = 1LL * p * q;
            } while (prod > MAXN);
            n = (int)prod;
        }
        tests.push_back(n);
    }

    // Output
    println(T);
    for (int x : tests) println(x);
    return 0;
}
