#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions and rotation count
    int N = inf.readInt(2, 300, "N");
    inf.readSpace();
    int M = inf.readInt(2, 300, "M");
    inf.readSpace();
    int R = inf.readInt(1, 1000, "R");
    inf.readEoln();

    // Check that the number of layers (min(N, M)/2) is integral,
    // i.e., min(N, M) must be even.
    ensuref(min(N, M) % 2 == 0,
            "min(N, M) must be even, but got N = %d, M = %d", N, M);

    // Read the matrix A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            inf.readInt(1, 100000000, "A_ij");
            if (j + 1 < M)
                inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
