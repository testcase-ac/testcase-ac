#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    int r = floor(sqrt(n));
    for (int i = 2; i <= r; ++i)
        if (n % i == 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Precompute small primes up to 1000 for power generation
    const int LIM = 1000;
    vector<bool> sieve(LIM + 1, true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i * i <= LIM; ++i)
        if (sieve[i])
            for (int j = i * i; j <= LIM; j += i)
                sieve[j] = false;
    vector<int> smallPrimes;
    for (int i = 2; i <= LIM; ++i)
        if (sieve[i]) smallPrimes.push_back(i);

    // Highly composite picks
    vector<int> highComp = {360, 840, 1260, 5040, 7560, 83160};

    // Choose hyper-parameter for N
    int type = rnd.next(0, 5);
    int N = 1;
    switch (type) {
        case 0:
            // Very small N
            N = rnd.next(1, 10);
            break;
        case 1:
            // Medium N
            N = rnd.next(10, 1000);
            break;
        case 2:
            // Large random N
            N = rnd.next(100000, 1000000);
            break;
        case 3:
            // Random prime up to 1e6
            while (true) {
                int cand = rnd.next(2, 1000000);
                if (isPrime(cand)) { N = cand; break; }
            }
            break;
        case 4:
            // Prime power p^e, e>=2
            while (true) {
                int p = rnd.any(smallPrimes);
                double maxE = log(1000000) / log(p);
                int emax = floor(maxE);
                if (emax >= 2) {
                    int e = rnd.next(2, emax);
                    long long v = 1;
                    for (int i = 0; i < e; ++i) v *= p;
                    if (v <= 1000000) { N = int(v); break; }
                }
            }
            break;
        case 5:
            // Highly composite number
            N = rnd.any(highComp);
            break;
    }

    // Ensure within bounds
    N = max(1, min(N, 1000000));
    println(N);
    return 0;
}
