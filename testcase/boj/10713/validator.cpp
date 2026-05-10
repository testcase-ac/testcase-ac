#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 100000, "M");
    inf.readEoln();

    // Read P_1 ... P_M
    vector<int> P = inf.readInts(M, 1, N, "P_j");
    inf.readEoln();

    // Check P_j != P_{j+1}
    for (int j = 0; j < M - 1; ++j) {
        ensuref(P[j] != P[j+1], "P_j == P_{j+1} at j = %d: %d", j+1, P[j]);
    }

    // Read A_i, B_i, C_i for i = 1..N-1
    for (int i = 0; i < N-1; ++i) {
        int A = inf.readInt(2, 100000, "A_i"); // A_i > B_i >= 1, so A_i >= 2
        inf.readSpace();
        int B = inf.readInt(1, A-1, "B_i"); // 1 <= B_i < A_i
        inf.readSpace();
        int C = inf.readInt(1, 100000, "C_i");
        inf.readEoln();

        // No further checks needed, as ranges above enforce all constraints
    }

    inf.readEof();
}
