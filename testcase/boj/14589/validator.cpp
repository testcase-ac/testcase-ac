#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of segments
    int N = inf.readInt(2, 150000, "N");
    inf.readEoln();

    // Read the segments
    for (int i = 0; i < N; i++) {
        int L = inf.readInt(-1000000, 1000000, "L_i");
        inf.readSpace();
        int R = inf.readInt(-1000000, 1000000, "R_i");
        inf.readEoln();
        ensuref(L <= R,
                "Segment %d is invalid: L_i (%d) must be <= R_i (%d)",
                i + 1, L, R);
    }

    // Read number of queries
    int Q = inf.readInt(1, 150000, "Q");
    inf.readEoln();

    // Read each query
    for (int i = 0; i < Q; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();
        ensuref(A != B,
                "Query %d is invalid: A_i and B_i must differ, got A=%d, B=%d",
                i + 1, A, B);
    }

    inf.readEof();
    return 0;
}
