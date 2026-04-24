#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C: natural numbers (i.e., >=1) and <=50
    int R = inf.readInt(1, 50, "R");
    inf.readSpace();
    int C = inf.readInt(1, 50, "C");
    inf.readEoln();

    // Counters for exactly one 'S' and one 'D'
    int sCount = 0, dCount = 0;

    // Read the grid
    for (int i = 0; i < R; i++) {
        // Read entire line (may contain any chars), then validate length and content
        string row = inf.readLine("[^]+", "row");
        ensuref((int)row.size() == C,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), C);
        for (int j = 0; j < C; j++) {
            char ch = row[j];
            ensuref(ch == '.' || ch == '*' || ch == 'X' || ch == 'D' || ch == 'S',
                    "Invalid character '%c' at row %d, column %d", ch, i+1, j+1);
            if (ch == 'S') sCount++;
            if (ch == 'D') dCount++;
        }
    }

    // Validate exactly one start and one destination
    ensuref(sCount == 1, "Found %d 'S' characters; exactly 1 required", sCount);
    ensuref(dCount == 1, "Found %d 'D' characters; exactly 1 required", dCount);

    inf.readEof();
    return 0;
}
