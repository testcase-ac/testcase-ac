#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases, assume up to 100,000 if not specified
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Each test consists of two integers m and n, 3 <= m,n <= 100
        int m = inf.readInt(3, 100, "m");
        inf.readSpace();
        int n = inf.readInt(3, 100, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
