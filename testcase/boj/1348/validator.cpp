#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions R and C
    int R = inf.readInt(1, 50, "R");
    inf.readSpace();
    int C = inf.readInt(1, 50, "C");
    inf.readEoln();

    // Read the grid and count cars and parking spots
    int cntC = 0, cntP = 0;
    for (int i = 0; i < R; i++) {
        // Each row must be exactly C characters among {C, P, X, .}
        string row = inf.readToken("[CPX.]{1,50}", "row");
        ensuref((int)row.size() == C,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), C);
        inf.readEoln();

        for (int j = 0; j < C; j++) {
            char ch = row[j];
            if (ch == 'C') {
                cntC++;
            } else if (ch == 'P') {
                cntP++;
            } else if (ch == 'X' || ch == '.') {
                // ok
            } else {
                // should never happen due to regex, but just in case
                ensuref(false,
                        "Invalid character '%c' at row %d, column %d", ch, i+1, j+1);
            }
        }
    }

    // Validate the counts of cars and parking zones
    ensuref(cntC <= 100,
            "Number of cars (%d) exceeds limit of 100", cntC);
    ensuref(cntP <= 100,
            "Number of parking spots (%d) exceeds limit of 100", cntP);

    inf.readEof();
    return 0;
}
