#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of cards to buy
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read P_1 ... P_N: prices of packs of size 1..N
    inf.readInts(N, 1, 10000, "P_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
