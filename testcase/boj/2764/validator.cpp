#include "testlib.h"

#include <cstdint>
#include <vector>

using namespace std;

int primeExponentInFactorial(int n, int p) {
    int result = 0;
    while (n > 0) {
        n /= p;
        result += n;
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The BOJ/Korean statement and official sample use a leading T,
    // while the English variant uses a terminating k = 0. Validate BOJ input.
    // CHECK: The BOJ statement does not bound T; cap it locally to keep inputs finite.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int k = inf.readInt(1, 5, "k");
        inf.readEoln();

        vector<int> n = inf.readInts(k, 1, 30, "n_i");
        inf.readEoln();

        int total = 0;
        for (int i = 0; i < k; ++i) {
            total += n[i];
            if (i > 0) {
                ensuref(n[i - 1] >= n[i],
                        "row lengths must be nonincreasing, but n_%d=%d < n_%d=%d",
                        i, n[i - 1], i + 1, n[i]);
            }
        }
        ensuref(total <= 30, "total number of students must be at most 30, got %d", total);

        vector<int> exponents(31, 0);
        const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        for (int p : primes) {
            exponents[p] = primeExponentInFactorial(total, p);
        }

        for (int row = 0; row < k; ++row) {
            for (int col = 1; col <= n[row]; ++col) {
                int below = 0;
                for (int nextRow = row + 1; nextRow < k; ++nextRow) {
                    if (n[nextRow] >= col) {
                        ++below;
                    }
                }

                int hookLength = n[row] - col + below + 1;
                int remaining = hookLength;
                for (int p : primes) {
                    while (remaining % p == 0) {
                        --exponents[p];
                        remaining /= p;
                    }
                }
                ensuref(remaining == 1, "unexpected hook length factorization remainder");
            }
        }

        uint64_t arrangements = 1;
        for (int p : primes) {
            ensuref(exponents[p] >= 0,
                    "negative exponent for prime %d while computing arrangement count", p);
            for (int i = 0; i < exponents[p]; ++i) {
                ensuref(arrangements <= 4294967295ULL / (uint64_t)p,
                        "number of arrangements exceeds unsigned 32-bit limit");
                arrangements *= (uint64_t)p;
            }
        }
    }

    inf.readEof();
}
