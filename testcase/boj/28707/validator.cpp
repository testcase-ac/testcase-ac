#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 8, "N");
    inf.readEoln();

    // Read array A of size N
    vector<int> A = inf.readInts(N, 1, 10, "A_i");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();

    // Read M operations
    for (int i = 0; i < M; i++) {
        int l = inf.readInt(1, N - 1, "l_i");
        inf.readSpace();
        // r must be strictly greater than l
        int r = inf.readInt(l + 1, N, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, 10, "c_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
