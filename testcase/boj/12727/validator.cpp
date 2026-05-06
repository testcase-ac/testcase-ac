#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Each test case: one integer n
    for (int tc = 1; tc <= T; tc++) {
        int n = inf.readInt(2, 30, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
