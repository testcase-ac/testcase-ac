#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<int> parent(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int l = inf.readInt(-1, n, "l");
        inf.readSpace();
        int r = inf.readInt(-1, n, "r");
        inf.readEoln();

        for (int child : {l, r}) {
            if (child == -1) {
                continue;
            }
            ensuref(child > i, "child bar %d of bar %d must be numbered after its parent", child, i);
            ensuref(parent[child] == 0, "bar %d appears below more than one bar", child);
            parent[child] = i;
        }
    }

    ensuref(parent[1] == 0, "bar 1 must be the top bar");

    for (int i = 2; i <= n; ++i) {
        ensuref(parent[i] != 0, "bar %d is not attached below the top bar", i);
    }

    inf.readEof();
}
