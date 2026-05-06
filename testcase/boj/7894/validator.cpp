#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Each test case: one integer m per line
    for (int i = 0; i < T; i++) {
        inf.readInt(1, 10000000, "m");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
