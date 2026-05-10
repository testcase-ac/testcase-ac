#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N, K, P, X on the first (and only) line
    long long N = inf.readLong(1LL, (long long)1e6, "N"); // temporary upper bound; refined below
    inf.readSpace();
    int K = inf.readInt(1, 6, "K");
    inf.readSpace();
    int P = inf.readInt(1, 42, "P");
    inf.readSpace();
    long long X = inf.readLong(1LL, N, "X");
    inf.readEoln();

    // Now enforce the tighter constraint N < 10^K
    long long tenPowK = 1;
    for (int i = 0; i < K; ++i) {
        tenPowK *= 10LL;
    }
    ensuref(N < tenPowK, "N must be less than 10^K: got N=%lld, K=%d, but 10^K=%lld", N, K, tenPowK);

    inf.readEof();
}
