#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "n");
    inf.readEoln();

    vector<vector<int>> children(n + 1);
    int edgeCount = 0;
    for (int employee = 1; employee <= n; ++employee) {
        int k = inf.readInt(0, n - 1, "k_i");
        edgeCount += k;
        ensuref(edgeCount <= 10000, "sum of k_i exceeds 10000");

        vector<bool> seen(n + 1, false);
        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            int boss = inf.readInt(1, n, "boss");
            // CHECK: The statement says the list contains employees accepted as bosses;
            // accepting oneself as one's boss would not define a useful hierarchy edge.
            ensuref(boss != employee, "employee %d lists themself as an accepted boss", employee);
            ensuref(!seen[boss], "employee %d lists boss %d more than once", employee, boss);
            seen[boss] = true;
            children[boss].push_back(employee);
        }
        inf.readEoln();
    }

    bool hasRoot = false;
    vector<int> visited(n + 1, 0);
    for (int root = 1; root <= n && !hasRoot; ++root) {
        queue<int> q;
        q.push(root);
        visited[root] = root;
        int reached = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            ++reached;
            for (int next : children[current]) {
                if (visited[next] != root) {
                    visited[next] = root;
                    q.push(next);
                }
            }
        }

        hasRoot = reached == n;
    }
    ensuref(hasRoot, "no valid restructuring exists");

    inf.readEof();
}
