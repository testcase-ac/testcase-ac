#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of bars
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // parent[i] will record the parent bar of bar i (0 = none)
    vector<int> parent(n+1, 0);

    // Read each bar's two attachments
    for (int i = 1; i <= n; i++) {
        int l = inf.readInt(-1, n, "l_i");
        inf.readSpace();
        int r = inf.readInt(-1, n, "r_i");
        inf.readEoln();

        // If left is a bar, check constraints and record parent
        if (l > 0) {
            ensuref(l > i,
                    "Left child bar %d of bar %d must have index > %d", l, i, i);
            ensuref(parent[l] == 0,
                    "Bar %d appears as a child of more than one parent", l);
            parent[l] = i;
        }
        // If right is a bar, check constraints and record parent
        if (r > 0) {
            ensuref(r > i,
                    "Right child bar %d of bar %d must have index > %d", r, i, i);
            ensuref(parent[r] == 0,
                    "Bar %d appears as a child of more than one parent", r);
            parent[r] = i;
        }
    }

    // Bar 1 must be the root (no parent)
    ensuref(parent[1] == 0, "Bar 1 must be the root of the mobile");

    // Every other bar must be connected (have exactly one parent)
    for (int i = 2; i <= n; i++) {
        ensuref(parent[i] != 0,
                "Bar %d is not connected to the root bar 1", i);
    }

    inf.readEof();
    return 0;
}
