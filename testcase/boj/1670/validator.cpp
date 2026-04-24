#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of participants, must be even and <= 10000.
    int N = inf.readInt(2, 10000, "N");
    ensuref(N % 2 == 0, "N (%d) must be even", N);

    // End of line after N
    inf.readEoln();
    // No more tokens
    inf.readEof();
    return 0;
}
