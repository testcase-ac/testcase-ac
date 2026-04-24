#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(0, 5000, "M");
    inf.readEoln();

    // Read M predictions (edges)
    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readEoln();
        // No further constraints on duplicates or self-loops are specified in the problem
    }

    inf.readEof();
    return 0;
}
