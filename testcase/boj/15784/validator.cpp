#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, a, b
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int a = inf.readInt(1, N, "a");
    inf.readSpace();
    int b = inf.readInt(1, N, "b");
    inf.readEoln();

    // Read the N x N matrix of charm values
    for (int i = 1; i <= N; i++) {
        // Read exactly N integers in [1,50000]
        inf.readInts(N, 1, 50000, "X_row");
        inf.readEoln();
    }

    // No additional global properties to check
    inf.readEof();
    return 0;
}
