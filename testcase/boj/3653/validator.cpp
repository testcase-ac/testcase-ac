#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: at most 100
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n and m
        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100000, "m");
        inf.readEoln();

        // Read the m queries: each between 1 and n
        inf.readInts(m, 1, n, "movie");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
