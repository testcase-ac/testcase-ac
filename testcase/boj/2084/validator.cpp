#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 2;
    const int N_MAX = 2000;

    int n = inf.readInt(N_MIN, N_MAX, "n");
    inf.readEoln();

    // Degree sequence: non-negative integers, each <= n-1
    vector<int> deg = inf.readInts(n, 0, n - 1, "d_i");
    inf.readEoln();

    // Basic implied constraint: sum of degrees must not exceed n*(n-1),
    // i.e., cannot require more than complete simple graph.
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += deg[i];
    }
    long long maxSum = 1LL * n * (n - 1);
    ensuref(sum <= maxSum,
            "Sum of degrees %lld exceeds maximum possible %lld for simple graph",
            sum, maxSum);

    // Note: we do NOT enforce that the degree sequence is graphical, nor
    // that the sum of degrees is even. The problem allows instances where
    // no graph exists; in that case, the correct output is -1. Those
    // properties must be handled by the solution, not the validator.

    inf.readEof();
}
