#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        // Read width and height (w and h)
        int w = inf.readInt(0, 50, "w");
        inf.readSpace();
        int h = inf.readInt(0, 50, "h");
        inf.readEoln();

        // Termination condition: both must be zero
        if (w == 0 || h == 0) {
            ensuref(w == 0 && h == 0,
                    "Termination line must have both w and h as zero, got w=%d, h=%d",
                    w, h);
            break;
        }

        // Now a real test case
        ++tc;
        ensuref(tc <= 100000, "Number of test cases exceeds 100000: %d", tc);

        // w and h must be positive here
        ensuref(w >= 1 && h >= 1,
                "In test case %d, expected w>=1 and h>=1, got w=%d, h=%d",
                tc, w, h);

        // Read the grid: h rows, each with w entries (0 or 1)
        for (int i = 0; i < h; i++) {
            vector<int> row = inf.readInts(w, 0, 1, "grid_cell");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
