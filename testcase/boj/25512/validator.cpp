#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<vector<int>> children(n);
    vector<int> parent_count(n, 0);
    for (int i = 0; i < n - 1; ++i) {
        int p = inf.readInt(0, n - 1, "p");
        inf.readSpace();
        int c = inf.readInt(0, n - 1, "c");
        inf.readEoln();

        ensuref(p != c, "edge %d has identical parent and child: %d", i + 1, p);
        // CHECK: The statement names p and c as parent and child with vertex 0 as root,
        // so validate the directed rooted-tree relation rather than only undirected tree shape.
        ensuref(c != 0, "root vertex 0 cannot be a child at edge %d", i + 1);
        ensuref(parent_count[c] == 0, "vertex %d has more than one parent", c);

        ++parent_count[c];
        children[p].push_back(c);
    }

    ensuref(parent_count[0] == 0, "root vertex 0 must not have a parent");
    for (int v = 1; v < n; ++v) {
        ensuref(parent_count[v] == 1, "vertex %d must have exactly one parent", v);
    }

    vector<int> seen(n, 0);
    queue<int> q;
    seen[0] = 1;
    q.push(0);
    int reached = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ++reached;
        for (int u : children[v]) {
            ensuref(!seen[u], "cycle reaches vertex %d from root", u);
            seen[u] = 1;
            q.push(u);
        }
    }
    ensuref(reached == n, "only %d of %d vertices are reachable from root 0", reached, n);

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 100000, "w");
        inf.readSpace();
        inf.readInt(1, 100000, "b");
        inf.readEoln();
    }

    inf.readEof();
}
