#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 10000, "K");
    inf.readEoln();

    // Read initial array values
    for (int i = 1; i <= N; i++) {
        inf.readInt(0, 1000000, "v_i");
        inf.readEoln();
    }

    // Read operations: total M updates (a=1) and K queries (a=2)
    int totalOps = M + K;
    int cntUpdate = 0;
    int cntQuery = 0;
    for (int i = 1; i <= totalOps; i++) {
        int a = inf.readInt(1, 2, "a_i");
        inf.readSpace();
        if (a == 1) {
            // update: b in [1,N], c in [0,1e6]
            int b = inf.readInt(1, N, "b_i");
            inf.readSpace();
            int c = inf.readInt(0, 1000000, "c_i");
            inf.readEoln();
            cntUpdate++;
        } else {
            // query: b,c are range endpoints in [1,N], and b <= c
            int b = inf.readInt(1, N, "b_i");
            inf.readSpace();
            int c = inf.readInt(1, N, "c_i");
            inf.readEoln();
            ensuref(b <= c, "For query %d: b_i (%d) must be <= c_i (%d)", i, b, c);
            cntQuery++;
        }
    }

    // Check counts match
    ensuref(cntUpdate == M, "Number of updates (a=1) is %d but expected M=%d", cntUpdate, M);
    ensuref(cntQuery  == K, "Number of queries (a=2) is %d but expected K=%d", cntQuery, K);

    inf.readEof();
    return 0;
}
