#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions R and C
    int R = inf.readInt(1, 300, "R");
    inf.readSpace();
    int C = inf.readInt(1, 300, "C");
    inf.readEoln();

    // Read the matrix rows
    for (int i = 0; i < R; i++) {
        // Read a token consisting of 0s and 1s
        string row = inf.readToken("[01]{1,300}", "row");
        // Check that its length matches C exactly
        ensuref((int)row.length() == C,
                "Length of row %d is %d but expected %d", i+1, (int)row.length(), C);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
