#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, S, M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int S = inf.readInt(0, 1000, "S");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();
    ensuref(S <= M,
            "Starting volume S must be ≤ M: got S = %d, M = %d",
            S, M);

    // Read V array of size N
    vector<int> V = inf.readInts(N, 1, M, "V");
    inf.readEoln();

    // No further global constraints (we don't compute the DP here)

    inf.readEof();
    return 0;
}
