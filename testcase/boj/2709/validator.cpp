#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    // Each test case: a single integer R
    for (int tc = 0; tc < T; tc++) {
        int R = inf.readInt(1, 20, "R");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
