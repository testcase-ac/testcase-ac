#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the integer N
    int N = inf.readInt(0, 9, "N");
    inf.readEoln();

    // No further input, so check for EOF
    inf.readEof();
}
