#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(1, 1000, "R");
    inf.readSpace();
    int C = inf.readInt(1, 1000, "C");
    inf.readEoln();

    // Read the R rows of the maze
    int jCount = 0;
    for (int i = 0; i < R; i++) {
        // Read entire line (no newline), then validate manually
        string row = inf.readLine("[^]+", "row");
        // Check length
        ensuref((int)row.size() == C,
                "Row %d length must be %d, but found %d", i+1, C, (int)row.size());
        // Check characters and count 'J'
        for (int j = 0; j < C; j++) {
            char ch = row[j];
            bool ok = (ch == '#' || ch == '.' || ch == 'J' || ch == 'F');
            ensuref(ok,
                    "Invalid character at row %d, col %d: '%c'", i+1, j+1, ch);
            if (ch == 'J') {
                jCount++;
            }
        }
    }

    // Exactly one J must be present
    ensuref(jCount == 1, "There must be exactly one 'J', but found %d", jCount);

    inf.readEof();
    return 0;
}
