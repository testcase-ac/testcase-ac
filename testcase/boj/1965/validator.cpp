#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of boxes
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // Read the sizes of the boxes
    inf.readInts(n, 1, 1000, "size_i");
    inf.readEoln();

    // No further constraints (LIS always exists at least of length 1)
    inf.readEof();
    return 0;
}
