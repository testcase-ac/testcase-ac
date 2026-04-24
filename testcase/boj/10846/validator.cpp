#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, A, B
    int N = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readEoln();

    // Check A ≤ B
    ensuref(A <= B, "A (%d) must be ≤ B (%d)", A, B);

    // Global constraint: if N > 100 then A == 1
    if (N > 100) {
        ensuref(A == 1,
                "When N (%d) > 100, A must be 1, but A = %d",
                N, A);
    }

    // Read Y_1 … Y_N
    vector<int> Y = inf.readInts(N, 0, 1000000000, "Y_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
