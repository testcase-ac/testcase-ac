#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const long long MAXB = 100000000000000LL;
    int mode = rnd.next(1, 5);
    long long A, B;
    vector<int> small_primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
    if (mode == 1) {
        // small range from 1
        A = 1;
        B = rnd.next(10, 200);
    } else if (mode == 2) {
        // small random interval
        A = rnd.next(2LL, 1000000LL);
        long long len = rnd.next(1LL, 1000LL);
        B = A + len;
        if (B > MAXB) B = MAXB;
    } else if (mode == 3) {
        // large interval near the top
        long long lo = rnd.next(1000000000000LL, MAXB - 1000000LL);
        A = lo;
        long long add = rnd.next(1000000LL, 10000000LL);
        B = A + add;
        if (B > MAXB) B = MAXB;
    } else if (mode == 4) {
        // around a prime power
        int p = rnd.any(small_primes);
        int k = rnd.next(2, 7);
        long double x = pow((long double)p, k);
        while (x > (long double)MAXB) {
            k = max(2, k - 1);
            x = pow((long double)p, k);
        }
        long long val = 1;
        for (int i = 0; i < k; i++) val *= p;
        long long dl = rnd.next(0LL, 50LL), dr = rnd.next(0LL, 50LL);
        A = max(1LL, val - dl);
        B = val + dr;
        if (B > MAXB) B = MAXB;
    } else {
        // single point: prime power or composite
        int typ = rnd.next(0, 1);
        if (typ == 0) {
            int p = rnd.any(small_primes);
            int k = rnd.next(2, 7);
            long double x = pow((long double)p, k);
            while (x > (long double)MAXB) {
                k = max(2, k - 1);
                x = pow((long double)p, k);
            }
            long long val = 1;
            for (int i = 0; i < k; i++) val *= p;
            A = B = val;
        } else {
            int p, q;
            do {
                p = rnd.any(small_primes);
                q = rnd.any(small_primes);
            } while (p == q);
            long long prod = (long long)p * q;
            A = B = prod;
        }
    }
    println(A, B);
    return 0;
}
