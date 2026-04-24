#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read the permutation on a single line
    vector<int> p(N);
    for (int i = 0; i < N; i++) {
        p[i] = inf.readInt(1, N, "p");
        if (i + 1 < N) {
            inf.readSpace();  // enforce separation by exactly one whitespace
        }
    }
    inf.readEoln();

    // Check that it's a valid permutation (no duplicates, all in [1..N])
    vector<bool> seen(N + 1, false);
    for (int i = 0; i < N; i++) {
        int v = p[i];
        // Range already checked by readInt
        ensuref(!seen[v],
                "Duplicate value %d found at position %d", v, i + 1);
        seen[v] = true;
    }
    // Since we read N values and none duplicated, all 1..N appear exactly once

    inf.readEof();
    return 0;
}
