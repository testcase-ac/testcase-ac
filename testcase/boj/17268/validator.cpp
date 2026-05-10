#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of participants
    // Constraint: N is an even integer, 2 <= N <= 10000
    int N = inf.readInt(2, 10000, "N");
    inf.readEoln();

    ensuref(N % 2 == 0, "N must be even, but got %d", N);

    inf.readEof();
}
