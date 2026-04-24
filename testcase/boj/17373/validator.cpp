#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M, Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Second line: the novel content array of length N
    inf.readInts(N, 1, M, "s_i");
    inf.readEoln();

    // Compute maximum possible K = M^2 (fits in 64-bit)
    long long maxK = (long long)M * (long long)M;
    // Next Q lines: each a query K
    for (int i = 0; i < Q; i++) {
        inf.readLong(1LL, maxK, "K_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
