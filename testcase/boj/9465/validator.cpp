#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n
        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();

        // Read first row of scores
        inf.readInts(n, 0, 100, "score_row1");
        inf.readEoln();

        // Read second row of scores
        inf.readInts(n, 0, 100, "score_row2");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
