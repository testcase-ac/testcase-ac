#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 10);
    vector<int> a(N);

    if (N == 1) {
        // Single element case
        a[0] = rnd.next(1, 1000000);
    } else if (rnd.next(0, 3) == 0) {
        // Pure random case to catch brute‐force failures
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, 1000000);
        }
    } else {
        // Generate numbers by distributing small prime factors
        vector<int> primes = {2, 3, 5, 7, 11};
        shuffle(primes.begin(), primes.end());
        int P = rnd.next(1, 3);
        primes.resize(P);

        // exp[i][j] = exponent of primes[j] in a[i]
        vector<vector<int>> exp(N, vector<int>(P, 0));
        for (int j = 0; j < P; j++) {
            // Total exponent sum for prime j
            int S = rnd.next(0, 2 * N);
            for (int k = 0; k < S; k++) {
                int i;
                // cap exponent at 2 per number
                do {
                    i = rnd.next(0, N - 1);
                } while (exp[i][j] >= 2);
                exp[i][j]++;
            }
        }

        for (int i = 0; i < N; i++) {
            long long val = 1;
            for (int j = 0; j < P; j++) {
                for (int t = 0; t < exp[i][j]; t++)
                    val *= primes[j];
            }
            a[i] = int(val);
        }
    }

    // Output the test case
    println(N);
    println(a);

    return 0;
}
