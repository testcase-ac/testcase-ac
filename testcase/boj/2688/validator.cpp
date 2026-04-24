#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Each test case: one integer n, 1 <= n <= 64
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        inf.readInt(1, 64, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
