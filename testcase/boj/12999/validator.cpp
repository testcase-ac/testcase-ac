#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read brightness values P[1..N]
    vector<int> P = inf.readInts(N, -100000, 100000, "P");
    inf.readEoln();

    // Read Q queries
    for (int i = 0; i < Q; i++) {
        int X = inf.readInt(1, N, "X");
        inf.readSpace();
        int Y = inf.readInt(1, N, "Y");
        inf.readEoln();
        ensuref(X <= Y,
                "Query %d: left index X (%d) must be <= right index Y (%d)",
                i + 1, X, Y);
    }

    inf.readEof();
    return 0;
}
