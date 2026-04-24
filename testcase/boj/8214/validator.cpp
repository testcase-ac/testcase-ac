#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and validate
    int n = inf.readInt(3, 3000, "n");
    ensuref(n % 3 == 0, "n must be divisible by 3, found n = %d", n);
    inf.readSpace();

    // Compute bounds for m
    int t = 2 * n / 3;  // size for the 2n/3 clique bound
    int minEdges = int((1LL * t * (t - 1)) / 2);
    int maxEdges = int((1LL * n * (n - 1)) / 2);

    // Read m and validate
    int m = inf.readInt(minEdges, maxEdges, "m");
    inf.readEoln();

    // Prepare for edge checks: no duplicates, a_i < b_i, 1 <= a,b <= n
    vector<char> seen((size_t)n * n, 0);

    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a < b,
                "Edge %d: expected a_i < b_i, but got a_i = %d, b_i = %d",
                i, a, b);

        int idx = (a - 1) * n + (b - 1);
        ensuref(!seen[idx],
                "Multiple edges detected between %d and %d at edge index %d",
                a, b, i);
        seen[idx] = 1;
    }

    inf.readEof();
    return 0;
}
