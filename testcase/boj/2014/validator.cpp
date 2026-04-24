#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and N
    int K = inf.readInt(1, 100, "K");
    inf.readSpace();
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the K primes
    vector<int> primes = inf.readInts(K, 2, 541, "p_i");
    inf.readEoln();

    // Check they are strictly increasing and actually prime
    for (int i = 0; i < K; i++) {
        if (i > 0) {
            ensuref(primes[i] > primes[i-1],
                    "p_i must be strictly increasing: p[%d]=%d <= p[%d]=%d",
                    i, primes[i], i-1, primes[i-1]);
        }
        int a = primes[i];
        for (int d = 2; d * d <= a; d++) {
            ensuref(a % d != 0,
                    "p_i is not prime: p[%d]=%d divisible by %d",
                    i, a, d);
        }
    }

    // According to the statement, the N-th product must be < 2^31.
    const long long LIMIT = (1LL << 31);

    // Generate the sequence of products (like humble numbers, but without 1 in final)
    // dp[0] = 1, and dp[1..N] are the first N products in increasing order.
    vector<long long> dp(N+1);
    dp[0] = 1;
    vector<int> idx(K, 0);
    vector<__int128> nextv(K);
    for (int j = 0; j < K; j++) {
        nextv[j] = primes[j];  // first candidate for each prime
    }

    for (int i = 1; i <= N; i++) {
        // find the next smallest product
        __int128 x = nextv[0];
        for (int j = 1; j < K; j++) {
            if (nextv[j] < x) x = nextv[j];
        }
        // Check the bound < 2^31
        ensuref(x < LIMIT,
                "The %d-th product = %lld is not less than 2^31", 
                i, (long long)x);
        dp[i] = (long long)x;
        // advance all indices that matched
        for (int j = 0; j < K; j++) {
            if (nextv[j] == x) {
                idx[j]++;
                nextv[j] = (__int128)primes[j] * dp[idx[j]];
            }
        }
    }

    // All input consumed
    inf.readEof();
    return 0;
}
