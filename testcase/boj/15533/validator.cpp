#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    vector<vector<int>> children(n + 1);

    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge index %d: (%d, %d)", i, a, b);
        ensuref(b != 1, "root node 1 has parent %d at edge index %d", a, i);
        ensuref(parent[b] == 0, "node %d has more than one parent", b);

        parent[b] = a;
        children[a].push_back(b);
    }

    for (int v = 2; v <= n; ++v) {
        ensuref(parent[v] != 0, "node %d has no parent", v);
    }

    vector<int> stack = {1};
    vector<char> seen(n + 1, false);
    seen[1] = true;
    int reached = 0;

    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        ++reached;

        for (int to : children[v]) {
            ensuref(!seen[to], "node %d is reachable more than once", to);
            seen[to] = true;
            stack.push_back(to);
        }
    }

    ensuref(reached == n, "graph is not connected from root 1: reached %d of %d nodes", reached, n);

    inf.readEof();
}
