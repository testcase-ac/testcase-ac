#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(2, 1000, "N");
    ensuref(N % 2 == 0, "N must be even, but got %d", N);
    inf.readSpace();
    int Q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    // Read Q operations
    for (int i = 0; i < Q; i++) {
        // Read the operation token
        string op = inf.readToken("[A-Z]+", "operation");
        if (op == "RO" || op == "RE" || op == "CO" || op == "CE") {
            // No further tokens on this line
            inf.readEoln();
        }
        else if (op == "S") {
            // Swap operation: S r1 c1 r2 c2
            inf.readSpace();
            int r1 = inf.readInt(1, N, "r1");
            inf.readSpace();
            int c1 = inf.readInt(1, N, "c1");
            inf.readSpace();
            int r2 = inf.readInt(1, N, "r2");
            inf.readSpace();
            int c2 = inf.readInt(1, N, "c2");
            inf.readEoln();
            ensuref(!(r1 == r2 && c1 == c2),
                    "Swap positions must be distinct, but both are (%d, %d)", r1, c1);
        }
        else {
            // Unknown command
            ensuref(false, "Unknown operation '%s' at query %d", op.c_str(), i+1);
        }
    }

    inf.readEof();
    return 0;
}
