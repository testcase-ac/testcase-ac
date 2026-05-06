#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: first line has N and K
    int N = inf.readInt(1, 20000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 50000, "K");
    inf.readEoln();

    // No further input allowed
    inf.readEof();
}
