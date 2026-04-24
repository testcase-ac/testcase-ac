#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: two integers n and m, 1 <= n, m <= 100
    for (int tc = 0; tc < T; tc++) {
        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100, "m");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
