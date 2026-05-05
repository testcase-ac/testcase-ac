#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 8, "N");
    inf.readSpace();
    int M = inf.readInt(1, 8, "M");
    ensuref(M <= N, "M (%d) must be <= N (%d)", M, N);
    inf.readEoln();

    // Read the N natural numbers
    inf.readInts(N, 1, 10000, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
