#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read n and m
        int n = inf.readInt(2, 50, "n");
        inf.readSpace();
        int m = inf.readInt(2, 50, "m");
        inf.readEoln();

        // Read the grid
        for (int i = 0; i < n; ++i) {
            // Each row has m integers in [0,1000]
            inf.readInts(m, 0, 1000, "a");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
