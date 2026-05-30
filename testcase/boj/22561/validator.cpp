#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 40000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 40000, "k");
    inf.readEoln();

    set<pair<int, int>> edges;

    for (int i = 0; i < k; ++i) {
        int type = inf.readInt(1, 3, "type_i");
        inf.readSpace();
        int u = inf.readInt(0, n - 1, "u_i");
        inf.readSpace();
        int v = inf.readInt(0, n - 1, "v_i");
        inf.readEoln();

        ensuref(u < v, "operation %d has u >= v: %d %d", i + 1, u, v);

        if (type == 1) {
            ensuref(edges.insert({u, v}).second,
                    "operation %d builds an existing edge: %d %d", i + 1, u, v);
        } else if (type == 2) {
            ensuref(edges.erase({u, v}) == 1,
                    "operation %d destroys a missing edge: %d %d", i + 1, u, v);
        }
    }

    inf.readEof();
}
