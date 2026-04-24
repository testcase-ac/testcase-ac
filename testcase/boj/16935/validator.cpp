#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M, R
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int M = inf.readInt(2, 100, "M");
    inf.readSpace();
    int R = inf.readInt(1, 1000, "R");
    inf.readEoln();

    // N and M must be even
    ensuref(N % 2 == 0, "N must be even, but got %d", N);
    ensuref(M % 2 == 0, "M must be even, but got %d", M);

    // Next N lines: the array A
    for (int i = 0; i < N; i++) {
        // Read exactly M integers in [1, 1e8]
        inf.readInts(M, 1, 100000000, "A_i_j");
        inf.readEoln();
    }

    // Last line: R operations in {1..6}
    inf.readInts(R, 1, 6, "op");
    inf.readEoln();

    inf.readEof();
    return 0;
}
