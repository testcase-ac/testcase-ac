#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int h = inf.readInt(3, 30, "H");
        inf.readSpace();
        int w = inf.readInt(3, 30, "W");
        inf.readSpace();
        inf.readInt(1, 50, "D");
        inf.readEoln();

        int xCount = 0;
        for (int row = 0; row < h; ++row) {
            string line = inf.readLine("[#.X]{3,30}", "row");
            ensuref((int)line.size() == w,
                    "row %d has length %d, expected %d", row + 1,
                    (int)line.size(), w);

            for (int col = 0; col < w; ++col) {
                char cell = line[col];
                if (row == 0 || row == h - 1 || col == 0 || col == w - 1) {
                    ensuref(cell == '#',
                            "border cell (%d, %d) is '%c', expected '#'",
                            row + 1, col + 1, cell);
                }
                if (cell == 'X') {
                    ++xCount;
                }
            }
        }

        ensuref(xCount == 1, "case has %d X cells, expected exactly one", xCount);
    }

    inf.readEof();
}
