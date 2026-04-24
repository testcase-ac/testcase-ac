#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(2, 1000000, "K");
    inf.readEoln();

    // Read the array A of size N
    vector<long long> A = inf.readLongs(N, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read each query and validate 1 ≤ l ≤ r ≤ N
    for (int i = 0; i < M; i++) {
        int l = inf.readInt(1, N, "l_i");
        inf.readSpace();
        int r = inf.readInt(1, N, "r_i");
        inf.readEoln();
        ensuref(l <= r,
                "Query %d is invalid: l (%d) must be ≤ r (%d)", 
                i+1, l, r);
    }

    inf.readEof();
    return 0;
}
