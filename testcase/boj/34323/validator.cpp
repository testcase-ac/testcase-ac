#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, S
    int N = inf.readInt(0, 100, "N");
    inf.readSpace();
    int M = inf.readInt(0, 100, "M");
    inf.readSpace();
    int S = inf.readInt(100, 100000000, "S");
    inf.readEoln();

    // No further constraints to check.
    // N: percent discount, 0 <= N <= 100
    // M: M+1 discount, 0 <= M <= 100
    // S: price, 100 <= S <= 1e8

    inf.readEof();
}
