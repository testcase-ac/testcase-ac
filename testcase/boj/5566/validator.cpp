#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read board instructions X[1..N]
    vector<int> X(N+1);
    for (int i = 1; i <= N; i++) {
        X[i] = inf.readInt(-999, 999, "X");
        inf.readEoln();
    }

    // Cells 1 and N must have instruction 0
    ensuref(X[1] == 0,
            "Instruction at cell 1 must be 0, found %d",
            X[1]);
    ensuref(X[N] == 0,
            "Instruction at cell N (%d) must be 0, found %d",
            N, X[N]);

    // No instruction sends you below cell 1
    for (int i = 1; i <= N; i++) {
        long dest = (long)i + X[i];
        ensuref(dest >= 1,
                "Instruction at cell %d moves to cell %ld which is < 1",
                i, dest);
    }

    // Read dice rolls
    vector<int> roll(M);
    for (int j = 0; j < M; j++) {
        roll[j] = inf.readInt(1, 6, "roll");
        inf.readEoln();
    }

    // Simulate to ensure reachability within M rolls
    long long pos = 1;
    bool reached = false;
    for (int j = 0; j < M; j++) {
        pos += roll[j];
        if (pos >= N) {
            reached = true;
            break;
        }
        // apply board instruction once
        pos += X[pos];
        if (pos >= N) {
            reached = true;
            break;
        }
    }
    ensuref(reached,
            "It is impossible to reach cell N within %d dice rolls",
            M);

    inf.readEof();
    return 0;
}
