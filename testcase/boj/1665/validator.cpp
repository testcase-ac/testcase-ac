#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of segments for train A
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read segments for train A
    for (int i = 0; i < N; i++) {
        int X = inf.readInt(1, 1000000000, "X_i");
        inf.readSpace();
        int Y = inf.readInt(1, 1000000000, "Y_i");
        inf.readEoln();
        ensuref(X <= Y,
                "For train A segment %d: X_i (%d) must be <= Y_i (%d)",
                i, X, Y);
    }

    // Read number of segments for train B
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read segments for train B
    for (int i = 0; i < M; i++) {
        int Z = inf.readInt(1, 1000000000, "Z_i");
        inf.readSpace();
        int W = inf.readInt(1, 1000000000, "W_i");
        inf.readEoln();
        ensuref(Z <= W,
                "For train B segment %d: Z_i (%d) must be <= W_i (%d)",
                i, Z, W);
    }

    // No extra data
    inf.readEof();
}
