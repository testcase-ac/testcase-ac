#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: not specified explicitly, so assume 1 to 100,000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 0; i < T; i++) {
        setTestCase(i + 1);
        // Each test case: one integer n, 1 <= n <= 100000
        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
