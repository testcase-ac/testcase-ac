#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "M");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at %d", i + 1, u);
        // CHECK: The statement does not forbid multiple trails between the same two bushes.
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> stack = {1};
    vector<bool> seen(n + 1, false);
    seen[1] = true;
    for (int head = 0; head < static_cast<int>(stack.size()); ++head) {
        int cur = stack[head];
        for (int next : graph[cur]) {
            if (!seen[next]) {
                seen[next] = true;
                stack.push_back(next);
            }
        }
    }

    ensuref(static_cast<int>(stack.size()) == n,
            "graph is disconnected: reached %d of %d bushes",
            static_cast<int>(stack.size()),
            n);

    inf.readEof();
}
