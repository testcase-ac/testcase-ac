#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n: number of vertices
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    vector<int> p(n + 1, 0);
    vector<int> used(n + 1, 0);

    for (int k = 1; k <= n; ++k) {
        int val = inf.readInt(1, n, "p_k");
        p[k] = val;
        inf.readEoln();

        ensuref(!used[val],
                "Permutation value %d appears multiple times (at least at position %d)",
                val, k);
        used[val] = 1;
    }

    // Ensure it's a valid permutation: every value 1..n used exactly once
    for (int v = 1; v <= n; ++v) {
        ensuref(used[v],
                "Permutation is incomplete: value %d does not appear", v);
    }

    inf.readEof();
}
