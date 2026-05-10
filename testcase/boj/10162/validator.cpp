#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    // No further input, so check for EOF
    inf.readEof();
}
