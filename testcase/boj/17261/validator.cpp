#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of tanks, must be N = 2^k - 1, 1 <= N <= 262143
    int N = inf.readInt(1, 262143, "N");
    inf.readEoln();
    // Check that N+1 is a power of two
    int x = N + 1;
    ensuref((x & (x - 1)) == 0,
            "N+1 = %d is not a power of two, so N = %d is not of the form 2^k - 1", x, N);

    // Read capacities W_i
    // There are exactly N integers, each in [1, 1e8]
    inf.readInts(N, 1, 100000000, "W_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
