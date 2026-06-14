#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 100, "m");
    inf.readSpace();
    int n = inf.readInt(0, 1000, "n");
    inf.readEoln();

    vector<vector<int>> graph(m);
    for (int i = 0; i < n; ++i) {
        int source = inf.readInt(0, m - 1, "source");
        inf.readSpace();
        int destination = inf.readInt(0, m - 1, "destination");
        inf.readSpace();
        inf.readInt(0, (1 << 15) - 1, "cost");
        inf.readEoln();

        // CHECK: The statement does not forbid self-loops or repeated directed links.
        graph[source].push_back(destination);
    }

    vector<bool> seen(m, false);
    queue<int> q;
    seen[0] = true;
    q.push(0);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int next : graph[node]) {
            if (!seen[next]) {
                seen[next] = true;
                q.push(next);
            }
        }
    }
    // CHECK: The output asks for a single path cost from Node 0 to Node 1, so unreachable inputs are undefined.
    ensuref(seen[1], "Node 1 must be reachable from Node 0");

    inf.readEof();
}
