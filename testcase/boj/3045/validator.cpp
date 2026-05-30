#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 500000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 100000, "M");
    inf.readEoln();

    // Read M operations
    for (int i = 0; i < M; i++) {
        // Operation type: 'A' or 'B'
        inf.readToken("[AB]", "op");
        inf.readSpace();
        // X and Y in [1, N]
        int X = inf.readInt(1, N, "X");
        inf.readSpace();
        int Y = inf.readInt(1, N, "Y");
        ensuref(X != Y, "X and Y must be distinct");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
