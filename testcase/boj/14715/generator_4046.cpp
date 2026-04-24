#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small primes for various constructions
    vector<int> small_primes = {
        2,3,5,7,11,13,17,19,23,29,
        31,37,41,43,47,53,59,61,67,71,
        73,79,83,89,97
    };
    // Some large primes near 1e6
    vector<int> large_primes = {
        999983, 999979, 999961, 999953, 999931
    };
    // Highly composite numbers under 1e6
    vector<int> highly_composite = {
        60, 360, 2520, 5040, 83160, 720720
    };

    // Choose a generation strategy
    int strategy = rnd.next(1, 6);
    int K = 2;
    switch (strategy) {
        case 1:
            // Small random K in [2,100]
            K = rnd.next(2, 100);
            break;
        case 2:
            // Pick a large prime
            K = rnd.any(large_primes);
            break;
        case 3: {
            // Prime power p^e, e>=2
            int p = rnd.any(small_primes);
            // compute max exponent
            vector<long long> powers;
            long long cur = p;
            powers.push_back(cur);
            while (cur <= 1000000LL / p) {
                cur *= p;
                powers.push_back(cur);
            }
            // we need exponent >=2 => index >=1
            if (powers.size() < 2) {
                // fallback to p^2
                K = p * p;
            } else {
                int idx = rnd.next(1, (int)powers.size() - 1);
                K = (int)powers[idx];
            }
            break;
        }
        case 4: {
            // Product of two distinct small primes
            int p1 = rnd.any(small_primes);
            int p2;
            do {
                p2 = rnd.any(small_primes);
            } while (p2 == p1);
            K = p1 * p2;
            break;
        }
        case 5:
            // Perfect square
            {
                int n = rnd.next(2, 1000);
                K = n * n;
            }
            break;
        case 6:
        default:
            // Fully random in [2,1e6]
            K = rnd.next(2, 1000000);
            break;
    }

    // Occasionally pick a highly composite number
    if (rnd.next(0, 4) == 0) {
        K = rnd.any(highly_composite);
    }

    // Ensure within bounds
    if (K < 2) K = 2;
    if (K > 1000000) K = 1000000;

    // Output single K
    println(K);
    return 0;
}
