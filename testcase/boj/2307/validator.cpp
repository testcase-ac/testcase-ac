#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(6, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(6, 5000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        int t = inf.readInt(1, 10000, "t");
        inf.readEoln();

        ensuref(a < b, "edge %d has endpoints not satisfying a < b: %d %d", i + 1, a, b);
        ensuref(edges.insert({a, b}).second, "duplicate road at edge %d: (%d, %d)", i + 1, a, b);

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // CHECK: The statement defines the delay against the normal fastest escape time, so require
    // at least one original route from 1 to N even though it is not stated as a separate input line.
    vector<int> stack = {1};
    vector<bool> seen(n + 1, false);
    seen[1] = true;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        for (int v : graph[u]) {
            if (!seen[v]) {
                seen[v] = true;
                stack.push_back(v);
            }
        }
    }
    ensuref(seen[n], "no route exists from 1 to N in the original graph");

    inf.readEof();
}
