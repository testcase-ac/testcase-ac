#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 1000000000, "n");
    inf.readEoln();

    // No further input, so check for EOF
    inf.readEof();
}
