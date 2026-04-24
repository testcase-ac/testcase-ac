#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of weights
    int n = inf.readInt(1, 9, "n");
    inf.readEoln();

    // Read the n distinct weights in strictly increasing order
    vector<int> w = inf.readInts(n, 1, 9, "weight");
    inf.readEoln();
    for (int i = 1; i < n; i++) {
        ensuref(w[i] > w[i-1],
                "Weights must be strictly increasing: w[%d]=%d <= w[%d]=%d",
                i-1, w[i-1], i, w[i]);
    }

    // Read k: the rank to query
    long long k = inf.readLong(0LL, 1000000000LL, "k");
    inf.readEoln();

    // No further global constraints on existence of balance configurations,
    // solution will handle emptiness / default output.

    inf.readEof();
    return 0;
}
