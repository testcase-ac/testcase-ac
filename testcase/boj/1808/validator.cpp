#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The written N bound starts at 1, but H must be in [1, N - 1],
    // so no complete input exists for N = 1.
    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    vector<int> parent(n, -1);
    vector<vector<int>> children(n);
    for (int i = 0; i < n - 1; ++i) {
        int a = inf.readInt(0, n - 1, "a");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "b");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop at vertex %d", i + 1, a);
        ensuref(b != 0, "edge %d assigns a parent to root 0", i + 1);
        ensuref(parent[b] == -1,
                "vertex %d has multiple parents: %d and %d", b, parent[b], a);

        parent[b] = a;
        children[a].push_back(b);
    }

    for (int v = 1; v < n; ++v) {
        ensuref(parent[v] != -1, "vertex %d has no parent", v);
    }

    vector<int> state(n, 0);
    auto dfs = [&](auto&& self, int v) -> void {
        ensuref(state[v] == 0, "cycle reaches vertex %d", v);
        state[v] = 1;
        for (int to : children[v]) {
            self(self, to);
        }
        state[v] = 2;
    };
    dfs(dfs, 0);

    for (int v = 0; v < n; ++v) {
        ensuref(state[v] == 2, "vertex %d is not reachable from root 0", v);
    }

    int h = inf.readInt(1, n - 1, "H");
    inf.readEoln();
    inf.readEof();
}
