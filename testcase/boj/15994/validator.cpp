#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 50000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read elevators' parameters
    for (int i = 1; i <= M; i++) {
        int X = inf.readInt(1, N, "X_" + to_string(i));
        inf.readSpace();
        int Y = inf.readInt(1, N, "Y_" + to_string(i));
        inf.readEoln();
    }

    // Read start and destination floors
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readEoln();

    // Validate A != B as guaranteed by the problem
    ensuref(A != B, "A and B must be different, but both are %d", A);

    // No more input
    inf.readEof();
    return 0;
}
