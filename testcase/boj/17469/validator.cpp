#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 1000000, "q");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; ++i) {
        parent[i] = inf.readInt(1, n, "p_i");
        inf.readEoln();
        ensuref(parent[i] != i, "node %d cannot be its own parent", i);
        children[parent[i]].push_back(i);
    }

    vector<int> seen(n + 1, 0);
    vector<int> stack = {1};
    seen[1] = 1;
    int visited = 0;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        ++visited;
        for (int v : children[u]) {
            ensuref(!seen[v], "cycle reaches node %d", v);
            seen[v] = 1;
            stack.push_back(v);
        }
    }
    ensuref(visited == n, "parent list must form a rooted tree at 1");

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100000, "c_i");
        inf.readEoln();
    }

    vector<int> deleted(n + 1, 0);
    int deleteQueries = 0;
    int reportQueries = 0;
    for (int i = 1; i <= n + q - 1; ++i) {
        int x = inf.readInt(1, 2, "x");
        inf.readSpace();
        int a = inf.readInt(1, n, "a");
        inf.readEoln();

        if (x == 1) {
            ++deleteQueries;
            ensuref(a != 1, "query %d deletes the root parent edge", i);
            ensuref(!deleted[a], "query %d deletes node %d more than once", i, a);
            deleted[a] = 1;
        } else {
            ++reportQueries;
        }
    }

    ensuref(deleteQueries == n - 1, "expected %d type-1 queries, found %d", n - 1,
            deleteQueries);
    ensuref(reportQueries == q, "expected %d type-2 queries, found %d", q, reportQueries);

    inf.readEof();
}
