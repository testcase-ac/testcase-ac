#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 191229, "T");
    inf.readEoln();

    // For each test case, read N
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // N must satisfy 1 <= N <= 191229
        inf.readInt(1, 191229, "N");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
