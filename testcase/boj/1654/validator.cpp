#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and N
    int K = inf.readInt(1, 10000, "K");
    inf.readSpace();
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();
    // Statement guarantees K <= N
    ensuref(K <= N,
            "Constraint violated: K must be <= N, but K=%d and N=%d", K, N);

    // Read the K cable lengths
    long long sum_lengths = 0;
    for (int i = 0; i < K; i++) {
        long long L = inf.readLong(1LL, 2147483647LL, "L_i");
        inf.readEoln();
        sum_lengths += L;
    }

    // Global property: it's assumed we can always make N cables (of length at least 1)
    // so sum of all lengths must be >= N
    ensuref(sum_lengths >= N,
            "Global constraint violated: sum of lengths (%lld) must be >= N (%d)",
            sum_lengths, N);

    inf.readEof();
    return 0;
}
