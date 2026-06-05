#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(0, n - 1, "k");
    inf.readEoln();

    vector<int> parent(n, -1);
    vector<vector<int>> children(n);
    for (int i = 0; i < n - 1; ++i) {
        int p = inf.readInt(0, n - 1, "p");
        inf.readSpace();
        int c = inf.readInt(0, n - 1, "c");
        inf.readEoln();

        ensuref(p != c, "edge %d has the same parent and child: %d", i + 1, p);
        ensuref(c != 0, "edge %d makes root vertex 0 a child", i + 1);
        ensuref(parent[c] == -1, "vertex %d has multiple parents", c);

        parent[c] = p;
        children[p].push_back(c);
    }

    for (int v = 1; v < n; ++v) {
        ensuref(parent[v] != -1, "non-root vertex %d has no parent", v);
    }

    vector<int> stack = {0};
    vector<bool> seen(n, false);
    seen[0] = true;
    int reachable = 0;
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        ++reachable;
        for (int child : children[v]) {
            ensuref(!seen[child], "cycle or duplicate reachability at vertex %d", child);
            seen[child] = true;
            stack.push_back(child);
        }
    }
    ensuref(reachable == n, "only %d of %d vertices are reachable from root 0", reachable, n);

    vector<bool> used_value(n, false);
    for (int i = 0; i < n; ++i) {
        int value = inf.readInt(0, n - 1, "value_i");
        ensuref(!used_value[value], "value %d appears multiple times", value);
        used_value[value] = true;
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    for (int value = 0; value < n; ++value) {
        ensuref(used_value[value], "value %d is missing from the vertex-value permutation", value);
    }
    ensuref(used_value[k], "queried value %d is missing", k);

    inf.readEof();
}
