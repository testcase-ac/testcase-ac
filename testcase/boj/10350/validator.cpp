#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of banks: 0 < n < 10000
    int n = inf.readInt(1, 9999, "n");
    inf.readEoln();

    // Read n capitals, each -31999 <= k_i <= 31999
    vector<int> capitals = inf.readInts(n, -31999, 31999, "k_i");
    inf.readEoln();

    // Global property: total capital must be positive
    long long total = 0;
    for (int x : capitals) {
        total += x;
    }
    ensuref(total > 0,
            "The total capital must be positive, but found %lld", total);

    inf.readEof();
    return 0;
}
