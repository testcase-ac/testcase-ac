#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    // No further input, so check for EOF
    inf.readEof();
}
