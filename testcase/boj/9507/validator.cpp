#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases: 0 < t < 69  => 1 <= t <= 68
    int t = inf.readInt(1, 68, "t");
    inf.readEoln();

    // Each test case: a single integer n with 0 <= n <= 67
    for (int i = 0; i < t; i++) {
        inf.readInt(0, 67, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
