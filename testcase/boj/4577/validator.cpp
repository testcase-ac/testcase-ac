#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int r = inf.readInt(0, 15, "R");
        inf.readSpace();
        int c = inf.readInt(0, 15, "C");
        inf.readEoln();

        if (r == 0 && c == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);
        // CHECK: The statement has no testcase-count bound; use the local default cap.
        ensuref(caseCount <= 100000, "too many test cases");
        ensuref(4 <= r && r <= 15, "R must be between 4 and 15, got %d", r);
        ensuref(4 <= c && c <= 15, "C must be between 4 and 15, got %d", c);

        int workers = 0;
        int boxes = 0;
        int targets = 0;
        int misplacedBoxes = 0;

        for (int i = 0; i < r; ++i) {
            string row = inf.readLine("[.#\\+bBwW]{1,15}", "row");
            ensuref((int)row.size() == c, "row %d has length %d, expected %d", i + 1,
                    (int)row.size(), c);

            for (int j = 0; j < c; ++j) {
                char cell = row[j];
                if (i == 0 || i == r - 1 || j == 0 || j == c - 1) {
                    ensuref(cell == '#', "boundary cell (%d,%d) is not a wall", i + 1, j + 1);
                }

                if (cell == 'w' || cell == 'W') {
                    ++workers;
                }
                if (cell == 'b' || cell == 'B') {
                    ++boxes;
                }
                if (cell == '+' || cell == 'B' || cell == 'W') {
                    ++targets;
                }
                if (cell == 'b') {
                    ++misplacedBoxes;
                }
            }
        }

        ensuref(workers == 1, "expected exactly one worker, got %d", workers);
        ensuref(boxes == targets, "box count %d does not equal target count %d", boxes, targets);
        ensuref(misplacedBoxes >= 1, "expected at least one box not on a target");

        inf.readLine("[UDLR]{0,50}", "moves");
    }

    inf.readEof();
}
