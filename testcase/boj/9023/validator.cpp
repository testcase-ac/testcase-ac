#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read C, D, d
        int C = inf.readInt(1, 10, "C");
        inf.readSpace();
        int D = inf.readInt(1, 10, "D");
        inf.readSpace();
        int d = inf.readInt(1, 10, "d");
        inf.readEoln();

        // Read sequence for team X
        int cntX = 0;
        bool first = true;
        while (true) {
            if (!first) {
                inf.readSpace();
            }
            first = false;
            int v = inf.readInt(0, 7, "x_seq");
            if (v == 0) {
                break;
            }
            // non-zero city must be 1..7 (readInt ensures <=7)
            ensuref(v >= 1, "Team X city out of range at test %d, pos %d: %d", tc, cntX+1, v);
            cntX++;
        }
        ensuref(cntX >= 3 && cntX <= 99,
                "Length of team X sequence out of bounds at test %d: %d (must be between 3 and 99)", 
                tc, cntX);
        inf.readEoln();

        // Read sequence for team Y
        int cntY = 0;
        first = true;
        while (true) {
            if (!first) {
                inf.readSpace();
            }
            first = false;
            int v = inf.readInt(0, 7, "y_seq");
            if (v == 0) {
                break;
            }
            ensuref(v >= 1, "Team Y city out of range at test %d, pos %d: %d", tc, cntY+1, v);
            cntY++;
        }
        ensuref(cntY >= 3 && cntY <= 99,
                "Length of team Y sequence out of bounds at test %d: %d (must be between 3 and 99)", 
                tc, cntY);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
