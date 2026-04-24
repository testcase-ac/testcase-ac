#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: one integer n
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        int n = inf.readInt(5, 100, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
