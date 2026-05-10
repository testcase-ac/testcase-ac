#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int K_MIN = 1, K_MAX = 100;
    const int N_MIN = 2, N_MAX = 5000;

    int test_case = 0;
    while (true) {
        // Read K and N
        int K = inf.readInt(0, K_MAX, "K"); // allow 0 for the ending line
        inf.readSpace();
        int N = inf.readInt(0, N_MAX, "N"); // allow 0 for the ending line
        inf.readEoln();

        if (K == 0 && N == 0) {
            break;
        }
        ++test_case;

        ensuref(K >= K_MIN && K <= K_MAX, "K out of bounds in test case %d: %d", test_case, K);
        ensuref(N >= N_MIN && N <= N_MAX, "N out of bounds in test case %d: %d", test_case, N);

        // Read adjacency lists
        std::vector< std::vector<int> > adj(N+1); // 1-based
        std::vector< std::set<int> > adj_set(N+1); // for duplicate check
        for (int i = 1; i <= N; ++i) {
            // Read a line of space-separated integers (at least one)
            // Use "[^]+" to match any non-empty line, then parse manually
            std::string line = inf.readLine("[^]+", "adjacency_list");
            ensuref(!line.empty(), "Empty adjacency list at node %d in test case %d", i, test_case);

            int pos = 0, len = line.length();
            while (pos < len) {
                // skip spaces
                while (pos < len && line[pos] == ' ') ++pos;
                if (pos >= len) break;
                int start = pos;
                while (pos < len && line[pos] >= '0' && line[pos] <= '9') ++pos;
                ensuref(start < pos, "Invalid token in adjacency list at node %d in test case %d", i, test_case);
                std::string token = line.substr(start, pos-start);
                // No leading zeros unless token is "0"
                ensuref(token.size() == 1 || token[0] != '0', "Leading zero in neighbor at node %d in test case %d", i, test_case);
                int v = atoi(token.c_str());
                ensuref(1 <= v && v <= N, "Neighbor %d at node %d in test case %d is out of bounds", v, i, test_case);
                ensuref(v != i, "Self-loop at node %d in test case %d", i, test_case);
                ensuref(!adj_set[i].count(v), "Duplicate neighbor %d at node %d in test case %d", v, i, test_case);
                adj[i].push_back(v);
                adj_set[i].insert(v);
            }
            ensuref(!adj[i].empty(), "Node %d in test case %d has no neighbors", i, test_case);
        }

        // Check that the graph is undirected: for every edge u-v, v-u must exist
        for (int u = 1; u <= N; ++u) {
            for (int v : adj[u]) {
                ensuref(adj_set[v].count(u), "Edge (%d,%d) is not bidirectional in test case %d", u, v, test_case);
            }
        }

        // Check that the graph is connected (from node 1)
        std::vector<bool> vis(N+1, false);
        std::queue<int> q;
        q.push(1);
        vis[1] = true;
        int cnt = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                    ++cnt;
                }
            }
        }
        ensuref(cnt == N, "Graph is not connected in test case %d (only %d/%d nodes reachable from 1)", test_case, cnt, N);
    }

    inf.readEof();
}
