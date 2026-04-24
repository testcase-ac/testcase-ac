#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(1, 10000, "R");
    inf.readSpace();
    int C = inf.readInt(5, 500, "C");
    inf.readEoln();

    // Read the grid
    for (int i = 0; i < R; i++) {
        // Read a line consisting only of '.' and 'x', length between 1 and 500
        string row = inf.readLine("[.x]{1,500}", "row");
        // Check exact length C
        ensuref((int)row.size() == C,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), C);
        // First and last column must be '.'
        ensuref(row[0] == '.',
                "Row %d: first character must be '.', found '%c'", i+1, row[0]);
        ensuref(row[C-1] == '.',
                "Row %d: last character must be '.', found '%c'", i+1, row[C-1]);
    }

    inf.readEof();
    return 0;
}
