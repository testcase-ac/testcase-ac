#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int N_MAX = 100;
const int M_MAX = N_MAX * (N_MAX - 1) / 2;
const int C_MIN = 1;
const int C_MAX = 1000;
const int T_MAX = 100000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, T_MAX, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int N = inf.readInt(2, N_MAX, "N");
        inf.readSpace();
        int M = inf.readInt(N - 1, N * (N - 1) / 2, "M");
        inf.readEoln();

        // Adjacency list for connectivity check and for global property check
        vector<vector<pair<int, int>>> adj(N + 1); // 1-based
        set<pair<int, int>> edge_set;

        for (int i = 0; i < M; ++i) {
            int a = inf.readInt(1, N, "a");
            inf.readSpace();
            int b = inf.readInt(1, N, "b");
            inf.readSpace();
            int c = inf.readInt(C_MIN, C_MAX, "c");
            inf.readEoln();

            ensuref(a != b, "Edge %d: loop detected (%d, %d)", i + 1, a, b);

            int u = min(a, b), v = max(a, b);
            ensuref(!edge_set.count({u, v}), "Edge %d: multiple edge detected between %d and %d", i + 1, u, v);
            edge_set.insert({u, v});

            adj[a].emplace_back(b, c);
            adj[b].emplace_back(a, c);
        }

        // Check graph is connected (BFS)
        vector<bool> vis(N + 1, false);
        queue<int> q;
        q.push(1);
        vis[1] = true;
        int vis_cnt = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &p : adj[u]) {
                int v = p.first;
                if (!vis[v]) {
                    vis[v] = true;
                    ++vis_cnt;
                    q.push(v);
                }
            }
        }
        ensuref(vis_cnt == N, "Graph is not connected: only %d/%d rooms are reachable from room 1", vis_cnt, N);

        int K = inf.readInt(1, N, "K");
        inf.readEoln();

        vector<int> friends = inf.readInts(K, 1, N, "friends");
        inf.readEoln();

        // Check friends' rooms are unique
        set<int> friend_rooms;
        for (int i = 0; i < K; ++i) {
            int room = friends[i];
            ensuref(friend_rooms.insert(room).second, "Duplicate friend room at index %d: room %d", i + 1, room);
        }

        // No further lines for this test case
    }

    inf.readEof();
}
