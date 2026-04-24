#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read Subin's and sibling's positions, both between 0 and 100000 inclusive
    int N = inf.readInt(0, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(0, 100000, "K");
    inf.readEoln();

    // No further input expected
    inf.readEof();
    return 0;
}
