#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read h and w
    int h = inf.readInt(1, 500, "h");
    inf.readSpace();
    int w = inf.readInt(1, 500, "w");
    inf.readEoln();

    // Read the altitude grid
    vector<vector<int>> alt(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        vector<int> row = inf.readInts(w, -1000000, 1000000, "altitude");
        for (int j = 0; j < w; j++) {
            alt[i][j] = row[j];
        }
        inf.readEoln();
    }

    // Read the drain device position
    int di = inf.readInt(1, h, "i");
    inf.readSpace();
    int dj = inf.readInt(1, w, "j");
    inf.readEoln();

    // Check that the device is placed on a water cell (altitude < 0)
    ensuref(alt[di-1][dj-1] < 0,
            "Device must be placed on a water cell (negative altitude), but altitude at (%d, %d) is %d",
            di, dj, alt[di-1][dj-1]);

    inf.readEof();
    return 0;
}
