#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read sizes of left shoes
    inf.readInts(N, 1, 1000000000, "L_i");
    inf.readEoln();

    // Read sizes of right shoes
    inf.readInts(M, 1, 1000000000, "R_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
