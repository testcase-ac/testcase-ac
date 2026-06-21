#include "testlib.h"

#include <queue>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);
    for (int i = 0; i < n; ++i) {
        int k = inf.readInt(0, n - 1, "K");
        set<int> seen;
        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            int destination = inf.readInt(0, n - 1, "destination");
            // CHECK: The statement does not explicitly ban duplicate
            // destinations, but "connections" are treated as graph edges.
            ensuref(seen.insert(destination).second,
                    "duplicate destination %d on planet %d", destination, i);
            graph[i].push_back(destination);
            ++indegree[destination];
        }
        inf.readEoln();
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        ++visited;
        for (int next : graph[current]) {
            --indegree[next];
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    ensuref(visited == n, "hyperspace connection network must be loop-free");

    inf.readEof();
}
