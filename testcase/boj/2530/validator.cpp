#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read current time: A B C
    int A = inf.readInt(0, 23, "A");
    inf.readSpace();
    int B = inf.readInt(0, 59, "B");
    inf.readSpace();
    int C = inf.readInt(0, 59, "C");
    inf.readEoln();

    // Read cooking time D
    int D = inf.readInt(0, 500000, "D");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
