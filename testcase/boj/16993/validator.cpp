#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read array A of size N
    vector<int> A = inf.readInts(N, -1000, 1000, "A_i");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M queries
    for (int qi = 0; qi < M; ++qi) {
        int i = inf.readInt(1, N, "query_i");
        inf.readSpace();
        int j = inf.readInt(1, N, "query_j");
        inf.readEoln();
        ensuref(i <= j,
                "In query %d: left index i (%d) must be <= right index j (%d)",
                qi+1, i, j);
    }

    inf.readEof();
    return 0;
}
