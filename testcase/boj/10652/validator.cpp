#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int b = inf.readInt(1, 40000, "B");
    inf.readSpace();
    int e = inf.readInt(1, 40000, "E");
    inf.readSpace();
    int p = inf.readInt(1, 40000, "P");
    inf.readSpace();
    int n = inf.readInt(3, 40000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 40000, "M");
    inf.readEoln();

    (void)b;
    (void)e;
    (void)p;

    vector<vector<int>> graph(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "connection %d must be between different fields: %d %d", i, u, v);
        // CHECK: repeated undirected connections are accepted because the statement
        // only says each connection joins a pair of different fields.
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto reaches_barn = [&](int start) {
        vector<char> seen(n + 1, false);
        queue<int> q;
        seen[start] = true;
        q.push(start);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int next : graph[cur]) {
                if (!seen[next]) {
                    seen[next] = true;
                    q.push(next);
                }
            }
        }
        return seen[n];
    };

    ensuref(reaches_barn(1), "field 1 must be connected to barn field %d", n);
    ensuref(reaches_barn(2), "field 2 must be connected to barn field %d", n);

    inf.readEof();
}
