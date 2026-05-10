#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read R, C
        int R = inf.readInt(2, 10, "R");
        inf.readSpace();
        int C = inf.readInt(2, 10, "C");
        inf.readEoln();

        // Read R lines of C characters, each line only contains '#' or '.'
        vector<string> grid(R);
        for (int i = 0; i < R; ++i) {
            grid[i] = inf.readLine("[#.]{"+to_string(C)+","+to_string(C)+"}", "grid row");
            ensuref((int)grid[i].size() == C, "Line %d of testcase %d: expected length %d, got %d", i+1, tc, C, (int)grid[i].size());
        }
    }

    inf.readEof();
}
