#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 1000;
    const int maxM = 10000;
    int testCases = 0;
    int totalN = 0;
    int totalM = 0;

    while (true) {
        int n = inf.readInt(0, maxN, "n");
        inf.readSpace();
        int m = inf.readInt(0, maxM, "m");
        inf.readEoln();

        if (n == 0 && m == 0) {
            inf.readEof();
            return 0;
        }

        ++testCases;
        setTestCase(testCases);
        ensuref(n >= 1, "n must be positive except for the 0 0 terminator");

        // CHECK: The statement gives no testcase-count bound; cap aggregate size
        // to one maximum testcase so validation remains finite and inspectable.
        ensuref(testCases <= 100000, "too many test cases: %d", testCases);
        totalN += n;
        totalM += m;
        ensuref(totalN <= maxN, "sum of n exceeds %d", maxN);
        ensuref(totalM <= maxM, "sum of m exceeds %d", maxM);

        vector<vector<int>> graph(n);
        vector<int> indegree(n, 0);
        for (int i = 0; i < m; ++i) {
            int a = inf.readInt(0, n - 1, "a");
            inf.readSpace();
            int b = inf.readInt(0, n - 1, "b");
            if (i + 1 < m) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }

            // CHECK: The statement says "graph" but does not forbid repeated
            // directed edges, so repeated edges are accepted when still acyclic.
            graph[a].push_back(b);
            ++indegree[b];
        }
        if (m == 0) {
            inf.readEoln();
        }

        vector<int> stones = inf.readInts(n, 0, 1000, "s_i");
        inf.readEoln();

        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int visited = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            ++visited;
            for (int to : graph[v]) {
                --indegree[to];
                if (indegree[to] == 0) {
                    q.push(to);
                }
            }
        }

        ensuref(visited == n, "the directed graph must be acyclic");
    }
}
