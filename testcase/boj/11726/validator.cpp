#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: the width of the rectangle
    int n = inf.readInt(1, 1000, "n");
    // After the integer, there must be exactly one end-of-line
    inf.readEoln();

    // No further input is allowed
    inf.readEof();
    return 0;
}
