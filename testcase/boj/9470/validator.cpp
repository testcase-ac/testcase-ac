#include "testlib.h"

#include <climits>
#include <queue>
#include <vector>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int K = inf.readInt(1, INT_MAX, "K");
        inf.readSpace();
        int M = inf.readInt(2, 1000, "M");
        inf.readSpace();
        int P = inf.readInt(1, INT_MAX, "P");
        inf.readEoln();

        std::vector<std::vector<int>> graph(M + 1);
        std::vector<int> indegree(M + 1, 0);
        std::vector<bool> hasOutgoing(M + 1, false);

        for (int i = 0; i < P; ++i) {
            int A = inf.readInt(1, M, "A");
            inf.readSpace();
            int B = inf.readInt(1, M, "B");
            inf.readEoln();

            ensuref(A != M, "node M (%d) must not have outgoing edges", M);
            hasOutgoing[A] = true;
            graph[A].push_back(B);
            ++indegree[B];
        }

        for (int node = 1; node < M; ++node) {
            ensuref(hasOutgoing[node], "node %d is also a mouth", node);
        }

        std::queue<int> q;
        for (int node = 1; node <= M; ++node) {
            if (indegree[node] == 0) {
                q.push(node);
            }
        }

        int visited = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            ++visited;

            for (int next : graph[node]) {
                --indegree[next];
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        ensuref(visited == M, "river system must be acyclic");
    }

    inf.readEof();
}
