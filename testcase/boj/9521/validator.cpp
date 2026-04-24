#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    // Read the array f of size N, each between 1 and N
    inf.readInts(N, 1, N, "f_i");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
