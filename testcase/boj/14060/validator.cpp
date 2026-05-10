#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    // Read m
    int m = inf.readInt(0, 3000, "m");
    inf.readEoln();

    // Read m edges
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge index %d: (%d, %d)", i + 1, u, v);
        // Multiedges are allowed, so no need to check for duplicates.
    }

    inf.readEof();
}
