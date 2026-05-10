#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Each test case
    for (int tc = 1; tc <= T; tc++) {
        inf.setTestCase(tc);

        // Number of operations
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        // Operations: each is one of U,D,F,B,L,R followed by + or -
        for (int i = 0; i < n; i++) {
            // Read the operation token
            inf.readToken("[UDFBLR][+-]", "operation");
            if (i + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
