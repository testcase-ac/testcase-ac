#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of chosen integers
    int N = inf.readInt(2, 30, "N");
    inf.readEoln();

    // No further input; ensure EOF
    inf.readEof();
}
