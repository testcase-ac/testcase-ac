#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of cards
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read the N card values
    inf.readInts(N, -10000000, 10000000, "cards");
    inf.readEoln();

    // Read M: number of queries
    int M = inf.readInt(1, 500000, "M");
    inf.readEoln();

    // Read the M query values
    inf.readInts(M, -10000000, 10000000, "queries");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
