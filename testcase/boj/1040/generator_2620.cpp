#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a small length for N (1 to 5 digits)
    int L = rnd.next(1, 5);
    // Precomputed powers of 10
    vector<long long> p10 = {1LL, 10LL, 100LL, 1000LL, 10000LL, 100000LL};

    long long lo = p10[L-1];
    long long hi = p10[L] - 1;
    long long N = rnd.next(lo, hi);

    // K: number of distinct digits allowed (1 to 10)
    int K = rnd.next(1, 10);

    // Output the single test case
    println(N, K);

    return 0;
}
