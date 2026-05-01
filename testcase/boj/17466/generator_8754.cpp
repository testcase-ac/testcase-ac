#include "testlib.h"
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (int d = 3; 1LL * d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

int randomPrime(int lo, int hi) {
    if (hi < 2) hi = 2;
    if (lo < 2) lo = 2;

    // Try random candidates first
    for (int iter = 0; iter < 100000; ++iter) {
        int x = rnd.next(lo, hi);
        if (x % 2 == 0) {
            if (x < hi) ++x;
            else if (x > lo) --x;
        }
        if (x < 2) x = 2;
        if (x > hi) x = hi - ((hi % 2 == 0) ? 1 : 0);
        if (x < lo) x = lo + ((lo % 2 == 0) ? 1 : 0);
        if (x >= lo && x <= hi && isPrime(x)) return x;
    }

    // Fallback: sequential search in [lo, hi]
    for (int x = lo; x <= hi; ++x)
        if (isPrime(x)) return x;

    // Global fallback (should never reach here in practice)
    for (int x = 2; x <= 100000000; ++x)
        if (isPrime(x)) return x;

    return 2; // absolute fallback
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, P;
    int type = rnd.next(1, 7);

    switch (type) {
        case 1: { // very small primes, varied N
            P = randomPrime(2, 50);
            int pattern = rnd.next(1, 4);
            if (pattern == 1) N = 1;
            else if (pattern == 2) N = P - 1;
            else if (pattern == 3) N = rnd.next(2, max(2, min(5, P - 1)));
            else N = rnd.next(1, P - 1);
            break;
        }
        case 2: { // medium P, very small N
            P = randomPrime(1000, 1000000);
            int upperN = min(10, P - 1);
            N = rnd.next(1, upperN);
            break;
        }
        case 3: { // N very close to P (P large-ish)
            P = randomPrime(1000, 100000000);
            int maxK = min(30, P - 1);
            int k = rnd.next(1, maxK);
            N = P - k;
            break;
        }
        case 4: { // random N and P, moderate size
            P = randomPrime(50, 1000000);
            N = rnd.next(1, P - 1);
            break;
        }
        case 5: { // N around P/2
            P = randomPrime(1000, 100000000);
            int base = P / 2;
            int delta = rnd.next(-5, 5);
            long long cand = 1LL * base + delta;
            if (cand < 1) cand = 1;
            if (cand >= P) cand = P - 1;
            N = (int)cand;
            break;
        }
        case 6: { // P near upper limit, N very close to P
            P = randomPrime(max(2, 100000000 - 2000), 100000000);
            int sub = rnd.next(1, 3);
            if (sub == 1) N = P - 1;
            else if (sub == 2) N = P - 2;
            else {
                int low = max(1, P - 50);
                N = rnd.next(low, P - 1);
            }
            break;
        }
        case 7: { // fully random P, structured N
            P = randomPrime(2, 100000000);
            int pattern = rnd.next(1, 4);
            if (pattern == 1) N = 1;
            else if (pattern == 2) N = P - 1;
            else if (pattern == 3) {
                int low = max(1, P / 2 - 5);
                int high = min(P - 1, P / 2 + 5);
                N = rnd.next(low, high);
            } else {
                N = rnd.next(1, P - 1);
            }
            break;
        }
        default: {
            P = randomPrime(2, 100000000);
            N = rnd.next(1, P - 1);
            break;
        }
    }

    println(N, P);
    return 0;
}
