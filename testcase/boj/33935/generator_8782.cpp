#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXN = 200;

    // Precompute primes up to MAXN
    vector<bool> isPrime(MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= MAXN; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAXN; j += i)
                isPrime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= MAXN; ++i)
        if (isPrime[i]) primes.push_back(i);

    // Precompute powers of two up to MAXN
    vector<int> pow2;
    for (int x = 1; x <= MAXN; x <<= 1)
        pow2.push_back(x);
    vector<bool> isPow2(MAXN + 1, false);
    for (int x : pow2)
        isPow2[x] = true;

    // Precompute perfect squares up to MAXN
    vector<int> squares;
    vector<bool> isSquare(MAXN + 1, false);
    for (int k = 1; k * k <= MAXN; ++k) {
        int v = k * k;
        squares.push_back(v);
        isSquare[v] = true;
    }

    // Precompute composites
    vector<bool> isComposite(MAXN + 1, false);
    for (int i = 2; i <= MAXN; ++i)
        if (!isPrime[i]) isComposite[i] = true;

    int scenario = rnd.next(1, 7);
    int N = 0;

    if (scenario == 1) {
        // Tiny N, emphasize very small values
        if (rnd.next(0, 1) == 0) {
            int special[] = {1, 2, 3, 4};
            N = special[rnd.next(0, 3)];
        } else {
            N = rnd.next(1, 10);
        }
    } else if (scenario == 2) {
        // Prime N
        N = rnd.any(primes);
    } else if (scenario == 3) {
        // Power of two
        N = rnd.any(pow2);
    } else if (scenario == 4) {
        // Perfect square
        N = rnd.any(squares);
    } else if (scenario == 5) {
        // Composite, not power of two and not perfect square
        for (int tries = 0; tries < 1000; ++tries) {
            int cand = rnd.next(2, MAXN);
            if (isComposite[cand] && !isPow2[cand] && !isSquare[cand]) {
                N = cand;
                break;
            }
        }
        if (N == 0) N = 12; // fallback (12 is composite, not pow2, not square)
    } else if (scenario == 6) {
        // Large-ish N near upper bound
        N = rnd.next(150, MAXN);
    } else if (scenario == 7) {
        // N with many divisors
        vector<int> rich = {60, 72, 84, 90, 96, 108, 120, 126, 132, 144, 168, 180, 192};
        N = rnd.any(rich);
    }

    println(N);
    return 0;
}
