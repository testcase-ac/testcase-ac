#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read H, W
        int H = inf.readInt(1, 100, "H");
        inf.readSpace();
        int W = inf.readInt(1, 100, "W");
        inf.readEoln();

        vector<string> grid(H);
        for (int i = 0; i < H; ++i) {
            grid[i] = inf.readLine("[#\\.]{"+to_string(W)+","+to_string(W)+"}", "grid_row");
            ensuref((int)grid[i].size() == W, "Row %d in test case %d does not have exactly W=%d characters", i+1, tc, W);
        }
    }

    inf.readEof();
}
