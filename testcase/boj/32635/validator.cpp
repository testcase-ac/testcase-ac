#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 1000000, "M");
    inf.readEoln();

    // Read array A of size N
    vector<int> A = inf.readInts(N, 1, 1000000, "A");
    inf.readEoln();

    // Read S and T
    int S = inf.readInt(1, N, "S");
    inf.readSpace();
    int T = inf.readInt(1, N, "T");
    ensuref(S != T, "S and T must be distinct, but both are %d", S);
    inf.readEoln();

    // Read M directed edges
    for (int i = 1; i <= M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        int c = inf.readInt(1, 1000000, "c_i");
        inf.readEoln();

        ensuref(u != v,
                "Self-loop detected at edge %d: %d -> %d", i, u, v);
    }

    inf.readEof();
    return 0;
}
