#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of towns N and roads M
    int N = inf.readInt(2, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M directed edges
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();
        // Self-loops are allowed by problem statement
        // Multiple edges are allowed by problem statement
    }

    // No extra data after last line
    inf.readEof();
    return 0;
}
