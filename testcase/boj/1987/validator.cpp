#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions R and C
    int R = inf.readInt(1, 20, "R");
    inf.readSpace();
    int C = inf.readInt(1, 20, "C");
    inf.readEoln();

    // Read the board rows
    for (int i = 0; i < R; ++i) {
        // Each row must consist of uppercase letters only
        string row = inf.readLine("[A-Z]+", "row");
        // Check the exact length matches C
        ensuref((int)row.size() == C,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), C);
    }

    inf.readEof();
    return 0;
}
