#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read array A of length N
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read each query: i, j with 1 <= i <= j <= N
    for (int q = 1; q <= M; q++) {
        int l = inf.readInt(1, N, "i");
        inf.readSpace();
        int r = inf.readInt(1, N, "j");
        inf.readEoln();
        ensuref(l <= r,
                "In query %d: left index i=%d is greater than right index j=%d",
                q, l, r);
    }

    inf.readEof();
    return 0;
}
