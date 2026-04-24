#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Read the array A of length N
    inf.readInts(N, 1, K, "A_i");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read each query (l, r)
    for (int i = 1; i <= M; i++) {
        int l = inf.readInt(1, N, "l_i");
        inf.readSpace();
        int r = inf.readInt(1, N, "r_i");
        ensuref(l <= r,
                "Query %d is invalid: l_i (%d) must be <= r_i (%d)",
                i, l, r);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
