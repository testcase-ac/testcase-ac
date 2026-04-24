#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int R = inf.readInt(1, 750, "R");
    inf.readSpace();
    int C = inf.readInt(1, 750, "C");
    inf.readEoln();

    // Read the grid rows
    for (int i = 0; i < R; i++) {
        // Each row must consist of exactly C characters, each '0' or '1'
        string row = inf.readLine("[01]{1,750}", "row");
        ensuref((int)row.length() == C,
                "Row %d length mismatch: expected %d, got %d",
                i + 1, C, (int)row.length());
    }

    inf.readEof();
    return 0;
}
