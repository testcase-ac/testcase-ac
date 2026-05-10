#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of rounds
    int N = inf.readInt(1, 300, "N");
    inf.readEoln();

    // Read sequences for both teams
    vector<int> A = inf.readInts(N, 1, 3, "A_i");
    inf.readEoln();
    vector<int> B = inf.readInts(N, 1, 3, "B_i");
    inf.readEoln();

    // First round must not be a draw
    ensuref(A[0] != B[0],
            "First round must not be a tie, but got A[0]=%d, B[0]=%d",
            A[0], B[0]);

    inf.readEof();
    return 0;
}
