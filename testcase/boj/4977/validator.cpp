#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalCells = 0;
    int dataset = 0;
    while (true) {
        int w = inf.readInt(0, 30, "w");
        inf.readSpace();
        int h = inf.readInt(0, 60, "h");
        inf.readEoln();

        if (w == 0 && h == 0) {
            ensuref(dataset > 0, "input must contain at least one dataset");
            break;
        }

        ++dataset;
        setTestCase(dataset);

        ensuref(2 <= w, "w must be at least 2, got %d", w);
        ensuref(5 <= h, "h must be at least 5, got %d", h);

        totalCells += 1LL * w * h;
        // CHECK: The statement gives no dataset-count bound; cap aggregate cells
        // to keep validation finite while still allowing 1000 maximum-size cases.
        ensuref(totalCells <= 1800000LL, "too many cliff cells across datasets");

        int starts = 0;
        int targets = 0;
        for (int y = 1; y <= h; ++y) {
            for (int x = 1; x <= w; ++x) {
                string cell = inf.readToken("[STX1-9]", "s_y_x");
                if (cell == "S") {
                    ensuref(y == h, "S appears outside the bottom row at (%d, %d)", x, y);
                    ++starts;
                } else if (cell == "T") {
                    ensuref(y == 1, "T appears outside the top row at (%d, %d)", x, y);
                    ++targets;
                }

                if (x == w) {
                    inf.readEoln();
                } else {
                    inf.readSpace();
                }
            }
        }

        ensuref(starts > 0, "dataset must contain at least one S in the bottom row");
        ensuref(targets > 0, "dataset must contain at least one T in the top row");
    }

    inf.readEof();
}
