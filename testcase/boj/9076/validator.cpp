#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        // Five judge scores per test case
        inf.readInts(5, 1, 10, "N_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
