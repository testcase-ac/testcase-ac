#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are exactly 4 scenarios (lines)
    const int LINES = 4;
    const int TEAMS = 6;
    for (int i = 0; i < LINES; i++) {
        // For each team, read wins, draws, losses
        for (int j = 0; j < TEAMS; j++) {
            // Read wins
            char bufW[20];
            sprintf(bufW, "w_%d_%d", i+1, j+1);
            int w = inf.readInt(0, 6, bufW);
            inf.readSpace();

            // Read draws
            char bufD[20];
            sprintf(bufD, "d_%d_%d", i+1, j+1);
            int d = inf.readInt(0, 6, bufD);
            inf.readSpace();

            // Read losses
            char bufL[20];
            sprintf(bufL, "l_%d_%d", i+1, j+1);
            int l = inf.readInt(0, 6, bufL);

            // After each team triple: either space (if more teams) or end-of-line
            if (j < TEAMS - 1) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }

            // Each team must have played exactly 5 matches
            int total = w + d + l;
            ensuref(total == 5,
                    "Line %d, team %d: wins+draws+losses must equal 5, got %d+%d+%d=%d",
                    i+1, j+1, w, d, l, total);
        }
    }

    // After the 4 lines, there must be no extra characters
    inf.readEof();
    return 0;
}
