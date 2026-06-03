#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; ++i) {
        parent[i] = inf.readInt(1, n, "a");
        inf.readEoln();
        ensuref(parent[i] != i, "vertex %d cannot be its own parent", i);
        children[parent[i]].push_back(i);
    }

    vector<int> stack = {1};
    vector<bool> seen(n + 1, false);
    seen[1] = true;
    int visited_count = 0;
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        ++visited_count;
        for (int to : children[v]) {
            ensuref(!seen[to], "cycle or duplicate visit involving vertex %d", to);
            seen[to] = true;
            stack.push_back(to);
        }
    }
    ensuref(visited_count == n, "parent list does not define a rooted tree at vertex 1");

    vector<bool> deleted(n + 1, false);
    int delete_count = 0;
    int query_count = 0;
    for (int i = 1; i <= (n - 1) + q; ++i) {
        int x = inf.readInt(0, 1, "x");
        inf.readSpace();
        if (x == 0) {
            int b = inf.readInt(2, n, "b");
            inf.readEoln();
            ensuref(!deleted[b], "edge to vertex %d is deleted more than once", b);
            deleted[b] = true;
            ++delete_count;
        } else {
            int c = inf.readInt(1, n, "c");
            inf.readSpace();
            int d = inf.readInt(1, n, "d");
            inf.readEoln();
            ++query_count;
        }
    }

    ensuref(delete_count == n - 1, "expected %d delete operations, found %d", n - 1, delete_count);
    ensuref(query_count == q, "expected %d query operations, found %d", q, query_count);

    inf.readEof();
}
