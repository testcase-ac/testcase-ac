#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, L
    int N = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 3000, "M");
    inf.readSpace();
    int L = inf.readInt(1, 30000, "L");
    inf.readEoln();

    // Read upper-cow x-coordinates U_i
    vector<int> U = inf.readInts(N, 0, 30000, "U_i");
    inf.readEoln();
    // They must be strictly increasing (distinct positions)
    for (int i = 1; i < N; i++) {
        ensuref(U[i] > U[i-1],
                "U_i not strictly increasing: U[%d]=%d <= U[%d]=%d",
                i-1, U[i-1], i, U[i]);
    }

    // Read lower-cow x-coordinates D_j
    vector<int> D = inf.readInts(M, 0, 30000, "D_j");
    inf.readEoln();
    // They must be strictly increasing (distinct positions)
    for (int j = 1; j < M; j++) {
        ensuref(D[j] > D[j-1],
                "D_j not strictly increasing: D[%d]=%d <= D[%d]=%d",
                j-1, D[j-1], j, D[j]);
    }

    // No more data
    inf.readEof();
    return 0;
}
