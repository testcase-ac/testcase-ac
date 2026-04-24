#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N
    int M = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Validate ordering
    ensuref(M <= N, "M (%d) must be <= N (%d)", M, N);

    // Sieve of Eratosthenes up to N
    vector<char> is_prime(N+1, true);
    if (N >= 0) is_prime[0] = false;
    if (N >= 1) is_prime[1] = false;
    for (int p = 2; (long long)p * p <= N; ++p) {
        if (is_prime[p]) {
            for (int q = p * p; q <= N; q += p)
                is_prime[q] = false;
        }
    }

    // Check that there is at least one prime in [M, N]
    bool has_prime = false;
    int start = max(M, 2);
    for (int x = start; x <= N; ++x) {
        if (is_prime[x]) {
            has_prime = true;
            break;
        }
    }
    ensuref(has_prime, "No prime exists in the interval [%d, %d]", M, N);

    // End of file
    inf.readEof();
    return 0;
}
