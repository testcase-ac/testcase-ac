#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M on a single line
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(2, N, "M");
    inf.readEoln();

    // No further input
    inf.readEof();

    return 0;
}
