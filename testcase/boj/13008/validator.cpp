#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2500, "m");
    inf.readSpace();
    int c = inf.readInt(0, 1000, "c");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    for (int i = 1; i <= m; ++i) {
        int from = inf.readInt(1, n, "from");
        inf.readSpace();
        int to = inf.readInt(1, n, "to");
        inf.readSpace();
        // CHECK: The prose says edge weights are positive, but the explicit
        // input bounds and samples allow cost = 0, so the numeric bounds win.
        int cost = inf.readInt(0, 100000, "cost");
        inf.readEoln();

        (void)cost;
        graph[from].push_back(to);
    }

    vector<int> stack = {1};
    vector<bool> seen(n + 1, false);
    seen[1] = true;
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        for (int to : graph[v]) {
            if (!seen[to]) {
                seen[to] = true;
                stack.push_back(to);
            }
        }
    }
    ensuref(seen[n], "vertex %d is not reachable from vertex 1", n);

    inf.readEof();
}
