#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<int> parent(n + 1);
    vector<vector<int>> children(n + 1);
    int root = 0;
    int root_count = 0;

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }

        parent[i] = inf.readInt(0, n, "parent_i");
        if (parent[i] == 0) {
            root = i;
            ++root_count;
        } else {
            ensuref(parent[i] != i, "vertex %d cannot be its own parent", i);
            children[parent[i]].push_back(i);
        }
    }
    inf.readEoln();

    ensuref(root_count == 1, "expected exactly one root, found %d", root_count);

    vector<int> stack;
    vector<char> visited(n + 1, 0);
    stack.push_back(root);
    visited[root] = 1;
    int seen = 0;

    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        ++seen;

        for (int u : children[v]) {
            ensuref(!visited[u], "vertex %d is reached more than once", u);
            visited[u] = 1;
            stack.push_back(u);
        }
    }

    ensuref(seen == n, "parent list must define one tree rooted at %d; reached %d of %d vertices", root, seen, n);

    inf.readEof();
}
