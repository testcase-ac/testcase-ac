#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Read each test case
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // N: age at death (0 ≤ N ≤ 1e9)
        int N = inf.readInt(0, 1000000000, "N");
        inf.readSpace();
        // M: day of death (1 ≤ M ≤ 1e9)
        int M = inf.readInt(1, 1000000000, "M");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
