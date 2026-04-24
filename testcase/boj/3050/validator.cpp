#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions R and C
    int R = inf.readInt(1, 400, "R");
    inf.readSpace();
    int C = inf.readInt(1, 400, "C");
    inf.readEoln();

    // Read the grid: R lines of exactly C characters: '.' or 'X'
    for (int i = 0; i < R; i++) {
        // Read a line with only '.' or 'X', length between 1 and 400
        string row = inf.readLine("[.X]{1,400}", "row");
        // Check exact length
        ensuref((int)row.size() == C,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), C);
        // (The regex already ensures only '.' and 'X' appear.)
    }

    // No extra characters after the grid
    inf.readEof();
    return 0;
}
