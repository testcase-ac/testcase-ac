#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 50000, "K");
    inf.readEoln();

    // Read prices v_i
    vector<int> v = inf.readInts(N, 1, 50000, "v_i");
    inf.readEoln();

    // Check non-decreasing sequence
    for (int i = 0; i + 1 < N; ++i) {
        ensuref(v[i] <= v[i + 1],
                "Sequence v must be non-decreasing, but v[%d]=%d > v[%d]=%d",
                i + 1, v[i], i + 2, v[i + 1]);
    }

    // No further global constraints are stated:
    // - Any partition into contiguous segments is allowed.
    // - It is always possible to use <= K bouquets (e.g., at least 1 bouquet).
    // So no simulation or extra checks are required.

    inf.readEof();
}
