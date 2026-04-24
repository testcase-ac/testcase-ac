#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 14, "N");
    inf.readSpace();
    int M = inf.readInt(1, 14, "M");
    inf.readEoln();

    // No further constraints on parity: odd area yields 0 ways, valid input.

    inf.readEof();
    return 0;
}
