#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Each test case: two integers A and B
    for (int tc = 1; tc <= T; tc++) {
        int A = inf.readInt(1, 1000000, "A");
        inf.readSpace();
        int B = inf.readInt(1, 1000000, "B");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
