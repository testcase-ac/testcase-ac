#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(2, 3000, "n");
    inf.readEoln();

    // Read coordinates x_1 ... x_n
    vector<long long> x = inf.readLongs(n, 1LL, 1000000000LL, "x");
    // Check strictly increasing
    for (int i = 1; i < n; i++) {
        ensuref(x[i] > x[i-1],
                "x[%d] = %lld is not strictly greater than x[%d] = %lld",
                i, x[i], i-1, x[i-1]);
    }
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
