#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: one integer k on first line, 2 ≤ k ≤ 10^12
    long long k = inf.readLong(2LL, 1000000000000LL, "k");
    inf.readEoln();

    // Additional global check (not strictly necessary, but validates a natural
    // implied property of the problem): there always exists at least one
    // multiset of integers > 1 whose product is exactly k.
    //
    // Reason: take the prime factorization of k; these primes are all >= 2
    // and their product is exactly k. So we can check by actually factoring k
    // that it decomposes into primes >= 2 and recombines to k.
    //
    // This also serves as a sanity check that no overflow occurs in product.
    long long tmp = k;
    vector<long long> factors;
    for (long long p = 2; p * p <= tmp; ++p) {
        while (tmp % p == 0) {
            factors.push_back(p);
            tmp /= p;
        }
    }
    if (tmp > 1) factors.push_back(tmp);

    // Recompute product to confirm correctness and no overflow.
    __int128 prod = 1;
    for (long long v : factors) {
        prod *= v;
    }
    ensuref(prod == ( __int128 )k,
            "Internal factorization check failed for k = %lld", k);
    ensuref(!factors.empty(),
            "There must exist at least one jewel weight > 1 (k >= 2 must have a factorization)");

    inf.readEof();
}
