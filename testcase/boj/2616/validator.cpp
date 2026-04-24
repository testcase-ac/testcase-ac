#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cars N
    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    // Read passengers in each car
    vector<int> p = inf.readInts(n, 0, 100, "passengers_i");
    inf.readEoln();

    // Compute maximum allowed m: must satisfy 1 <= m < n/3
    int maxM = (n - 1) / 3;
    ensuref(maxM >= 1,
            "n = %d is too small: no integer m >= 1 satisfies m < n/3", n);

    // Read m
    int m = inf.readInt(1, maxM, "m");
    // Double-check strictness (sanity)
    ensuref(3LL * m < n,
            "m must be strictly less than n/3, but got m = %d, n = %d", m, n);
    inf.readEoln();

    inf.readEof();
    return 0;
}
