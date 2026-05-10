#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K
    int K = inf.readInt(1, 10, "K");
    inf.readEoln();

    // Number of nodes in a complete binary tree of depth K
    int N = (1 << K) - 1;
    long long maxLabel = (1LL << K) - 1;

    // Read the visitation order: exactly N distinct integers in [1, 2^K - 1]
    vector<int> order = inf.readInts(N, 1LL, maxLabel, "order_i");
    inf.readEoln();

    // Check for duplicates
    vector<char> seen(maxLabel + 1, 0);
    for (int i = 0; i < N; i++) {
        int x = order[i];
        ensuref(!seen[x], "Duplicate building number at index %d: %d", i, x);
        seen[x] = 1;
    }

    inf.readEof();
    return 0;
}
