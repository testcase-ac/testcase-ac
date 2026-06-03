#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(0, n - 1, "a");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "b");
        inf.readEoln();

        ensuref(a != b, "self friendship at edge %d: %d", i + 1, a);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate friendship at edge %d: %d %d", i + 1, a, b);
    }

    inf.readEof();
}
