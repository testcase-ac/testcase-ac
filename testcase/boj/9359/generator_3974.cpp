#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    // Build a list of small primes up to 1000
    const int PMAX = 1000;
    vector<bool> is_com(PMAX+1, false);
    vector<int> primes;
    for (int i = 2; i <= PMAX; ++i) {
        if (!is_com[i]) {
            primes.push_back(i);
            for (long long j = 1LL*i*i; j <= PMAX; j += i)
                is_com[j] = true;
        }
    }

    // Primes whose square is <= 1e9
    vector<int> small_primes;
    for (int p : primes) {
        if ((long long)p * p <= 1000000000LL)
            small_primes.push_back(p);
    }

    const long long MAXB = 1000000000000000LL; // 1e15

    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter: choose type of N
        int typeN = rnd.next(0, 9);
        long long N;
        if (typeN == 0) {
            // Special case N = 1
            N = 1;
        } else if (typeN <= 3) {
            // A small prime
            N = rnd.any(primes);
        } else if (typeN <= 6) {
            // A square of a small prime
            N = (long long)rnd.any(small_primes) * rnd.any(small_primes);
        } else {
            // Product of two primes, ensure <= 1e9
            int p1 = rnd.any(primes), p2 = rnd.any(primes);
            while ((long long)p1 * p2 > 1000000000LL) {
                p1 = rnd.any(primes);
                p2 = rnd.any(primes);
            }
            N = (long long)p1 * p2;
        }

        // Hyper-parameter: choose range type
        int typeR = rnd.next(0, 2);
        long long A, B;
        if (typeR == 0) {
            // Small range [1..100]
            B = rnd.next(1LL, 100LL);
            A = rnd.next(1LL, B);
        } else if (typeR == 1) {
            // Medium range up to 1e9, length up to 1e6
            A = rnd.next(1LL, 1000000000LL);
            long long len = rnd.next(0LL, 1000000LL);
            B = A + len;
        } else {
            // Large range near 1e15, length up to 1e6
            B = rnd.next(MAXB - 1000000LL, MAXB);
            long long minA = max(1LL, B - 1000000LL);
            A = rnd.next(minA, B);
        }

        println(A, B, N);
    }

    return 0;
}
