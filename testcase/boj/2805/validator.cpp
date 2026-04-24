#include "testlib.h"
#include <cstdint>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000000000, "M");
    inf.readEoln();

    // Read tree heights
    vector<int> h = inf.readInts(n, 0, 1000000000, "h_i");
    inf.readEoln();

    // Check that sum of heights >= M, as guaranteed by problem
    // Use 64-bit to avoid overflow
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        sum += h[i];
    }
    ensuref(sum >= m,
            "Sum of all tree heights (%lld) is less than M (%d)",
            (long long)sum, m);

    inf.readEof();
    return 0;
}
