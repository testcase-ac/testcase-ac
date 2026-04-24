#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // For clearer error reporting per test case
        setTestCase(tc + 1);

        // Read two binary strings of length 1 to 80
        inf.readToken("[01]{1,80}", "A");
        inf.readSpace();
        inf.readToken("[01]{1,80}", "B");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
