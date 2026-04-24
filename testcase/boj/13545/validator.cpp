#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read sequence A of length N, values must be -1 or 1
    vector<int> A = inf.readInts(N, -1, 1, "A");
    for (int i = 0; i < N; i++) {
        ensuref(A[i] == -1 || A[i] == 1,
                "Invalid A[%d] = %d; expected -1 or 1", i+1, A[i]);
    }
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M queries
    for (int qi = 0; qi < M; qi++) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int j = inf.readInt(1, N, "j");
        inf.readEoln();
        ensuref(i <= j,
                "Query %d has i = %d > j = %d", qi+1, i, j);
    }

    inf.readEof();
    return 0;
}
