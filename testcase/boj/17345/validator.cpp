#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 50000, "M");
    inf.readEoln();

    // Second line: P_1..P_N
    vector<int> P = inf.readInts(N, 0, 100, "P_i");
    inf.readEoln();

    // Next M lines: A_i, B_i, C_i
    for (int i = 0; i < M; ++i) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readSpace();
        int C = inf.readInt(0, 100, "C_i");
        inf.readEoln();
        // No extra constraints (loops, multiple edges, etc.) are forbidden by statement,
        // so we only check ranges as above.
    }

    inf.readEof();
}
