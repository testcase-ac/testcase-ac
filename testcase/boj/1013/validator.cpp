#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases (1 ≤ T ≤ 100 000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each of the next T lines: a binary string of length 1..200
    for (int tc = 1; tc <= T; tc++) {
        inf.readToken("[01]{1,200}", "s");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
