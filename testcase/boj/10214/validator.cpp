#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case consists of 9 lines of two scores each
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        for (int i = 0; i < 9; i++) {
            int Y = inf.readInt(0, 9, "Y");
            inf.readSpace();
            int K = inf.readInt(0, 9, "K");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
