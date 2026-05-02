#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 200000, "N");
    inf.readEoln();

    // Read c_1 ... c_{N-1}
    vector<long long> c = inf.readLongs(N-1, 1LL, 1000000000000000000LL, "c_i");
    inf.readEoln();

    // No further global validation is needed:
    // - The problem guarantees that the input is always such that a valid visit order exists.
    // - No monotonicity, sum, or other global property is required to be checked by the validator.
    // - All constraints are local and already checked above.

    inf.readEof();
}
