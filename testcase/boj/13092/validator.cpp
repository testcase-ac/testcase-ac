#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 50, "K");
    inf.readEoln();

    // Validate relation N <= 2^K
    long long maxLeaves = 1LL << K;
    ensuref((long long)N <= maxLeaves,
            "Constraint violated: N must be <= 2^K, but N=%d > 2^%d=%lld", 
            N, K, maxLeaves);

    // Read strengths
    vector<int> A = inf.readInts(N, 1, 100000, "A_i");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
