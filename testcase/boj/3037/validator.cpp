#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and C according to problem constraints
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int C = inf.readInt(0, 10000, "C");
    // End of line after the only test case
    inf.readEoln();
    // No further input
    inf.readEof();

    return 0;
}
