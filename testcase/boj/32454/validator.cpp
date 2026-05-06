#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int t = inf.readInt(1, 20, "t");
    inf.readEoln();

    // Each test case: one integer n
    for (int i = 0; i < t; i++) {
        inf.readInt(1, 1000000000, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
