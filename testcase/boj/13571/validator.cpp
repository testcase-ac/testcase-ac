#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    // Precompute knight moves for all possible board sizes up to 2*12 = 24
    const int MAXN = 12;
    const int MAXB = 2 * MAXN;
    const long long K_MAX = 1000000000LL;
    const int MOD = 1000007;

    // Directions of knight moves
    const int dx[8] = {1,2, 2, 1,-1,-2,-2,-1};
    const int dy[8] = {2,1,-1,-2,-2,-1, 1, 2};

    // We'll build graphs on the fly per n to check "answer always exists" claim
    // State indexing: (x,y) -> id = x * B + y, where B = 2*n
    auto inside = [](int x, int y, int B) {
        return x >= 0 && x < B && y >= 0 && y < B;
    };

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);
        long long n = inf.readLong(2LL, 12LL, "n");
        inf.readSpace();
        long long k = inf.readLong(1LL, K_MAX, "k");
        inf.readEoln();

        int B = int(2 * n);
        int N = B * B;

        // Build adjacency list of knight graph for this n
        vector<vector<int>> adj(N);
        for (int x = 0; x < B; ++x) {
            for (int y = 0; y < B; ++y) {
                int id = x * B + y;
                for (int dir = 0; dir < 8; ++dir) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if (inside(nx, ny, B)) {
                        int nid = nx * B + ny;
                        adj[id].push_back(nid);
                    }
                }
            }
        }

        // Corners indices
        vector<int> corners;
        corners.push_back(0);                         // (0,0)
        corners.push_back(B - 1);                    // (0,B-1)
        corners.push_back((B - 1) * B);              // (B-1,0)
        corners.push_back((B - 1) * B + (B - 1));    // (B-1,B-1)

        // BFS from start to compute minimal distances to corners
        const int INF = (int)1e9;
        vector<int> dist(N, INF);
        queue<int> q;
        int start = 0; // (0,0)
        dist[start] = 0;
        q.push(start);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int to : adj[v]) {
                if (dist[to] == INF) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }

        int minCornerDist = INF;
        for (int c : corners) {
            if (dist[c] < minCornerDist) minCornerDist = dist[c];
        }

        // Problem text: "최대 K번 움직여서 모서리에 도착하는 방법의 수"
        // This implies that for given test, answer always exists for that K?
        // The statement does NOT explicitly guarantee existence for arbitrary K,
        // so we do NOT enforce any extra constraint here beyond the input ranges.
        // However, we at least check graph sanity and that corners are reachable at all.
        ensuref(minCornerDist < INF,
                "For n=%lld the knight cannot reach any corner at all, graph seems inconsistent", n);

        // Also check that minimal distance is not greater than K, otherwise certainly 0 ways.
        // The statement does not forbid this, so we allow k < minCornerDist (answer just 0).
        // Hence no additional ensure on relation between k and distances.

        // We also guard against overflow / extremely dense graphs: each node degree <= 8 by construction.
        for (int v = 0; v < N; ++v) {
            ensuref((int)adj[v].size() <= 8,
                    "Node %d in board size %d has degree %d > 8, invalid knight graph",
                    v, B, (int)adj[v].size());
        }

        // No further validation is required from statement.
    }

    inf.readEof();
}
