#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of operations
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Each of the next N lines contains exactly one integer x:
    // 0 ≤ x < 2^31, and no negatives are allowed.
    for (int i = 0; i < N; i++) {
        // We allow 0 (pop operation) or a natural number up to 2^31−1 (insert operation).
        inf.readLong(0, 2147483647LL, "x");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
