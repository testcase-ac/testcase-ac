#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX = 1299709;
    // Sieve for primes up to MAX
    vector<bool> isPrime(MAX+1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX; j += i)
                isPrime[j] = false;
        }
    }
    // Collect all primes, plus low-range and high-range primes
    vector<int> primes, lowPrimes, highPrimes;
    for (int i = 2; i <= MAX; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            if (i <= 1000) lowPrimes.push_back(i);
            if (i >= MAX - 1000) highPrimes.push_back(i);
        }
    }

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    // Probability that we pick a composite
    double pComposite = rnd.next();
    for (int it = 0; it < T; it++) {
        // Distribution choice: 0 = uniform, 1 = low region, 2 = high region
        int dist = rnd.next(0, 2);
        bool wantPrime = rnd.next() > pComposite;
        int k;
        if (wantPrime) {
            // Pick a prime according to dist
            if (dist == 1 && !lowPrimes.empty()) {
                k = rnd.any(lowPrimes);
            } else if (dist == 2 && !highPrimes.empty()) {
                k = rnd.any(highPrimes);
            } else {
                k = rnd.any(primes);
            }
        } else {
            // Pick a composite: sample until we get non-prime
            do {
                if (dist == 1) {
                    k = rnd.next(2, min(MAX, 1000));
                } else if (dist == 2) {
                    k = rnd.next(MAX - 1000, MAX);
                } else {
                    k = rnd.next(2, MAX);
                }
            } while (isPrime[k]);
        }
        println(k);
    }

    return 0;
}
