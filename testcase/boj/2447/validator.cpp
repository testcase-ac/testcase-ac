#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: must be a power of 3 with 1 <= k < 8, i.e., N in {3,9,27,81,243,729,2187}
    int N = inf.readInt(3, 2187, "N");
    inf.readEoln();

    // Check that N is exactly a power of 3 (3^k) for some k >= 1
    {
        int x = N;
        while (x % 3 == 0) {
            x /= 3;
        }
        ensuref(x == 1, "N is not a power of 3: %d", N);
    }

    // No more tokens
    inf.readEof();
    return 0;
}
