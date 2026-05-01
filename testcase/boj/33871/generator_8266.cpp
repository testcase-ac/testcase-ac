#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> smallPrimes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
    int type = rnd.next(0,5);
    long long N = 2;
    if (type == 0) {
        // Small N
        N = rnd.next(2, 50);
    } else if (type == 1) {
        // Small prime
        N = rnd.any(smallPrimes);
    } else if (type == 2) {
        // Large prime near 1e9
        vector<int> largePrimes = {999999937, 999999929, 999999893};
        N = rnd.any(largePrimes);
    } else if (type == 3) {
        // Prime power p^e
        int p = rnd.any(smallPrimes);
        long long prod = p;
        int e_max = 1;
        while (prod * p <= 1000000000LL) {
            prod *= p;
            e_max++;
        }
        int e = rnd.next(2, e_max);
        long long val = 1;
        for (int i = 0; i < e; i++) val *= p;
        N = val;
    } else if (type == 4) {
        // Product of two distinct small primes
        int p = rnd.any(smallPrimes);
        int q = rnd.any(smallPrimes);
        while (q == p) q = rnd.any(smallPrimes);
        N = 1LL * p * q;
    } else {
        // Factorial number
        vector<long long> fact(13);
        fact[0] = 1;
        for (int i = 1; i <= 12; i++) fact[i] = fact[i-1] * i;
        int k = rnd.next(2, 12);
        N = fact[k];
    }
    println(N);
    return 0;
}
