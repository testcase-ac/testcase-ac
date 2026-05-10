#include "testlib.h"
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int C = inf.readInt(3, 1000, "C");
        inf.readSpace();
        int R = inf.readInt(3, 1000, "R");
        inf.readEoln();

        vector<string> grid(R);
        long long freeCount = 0;

        for (int i = 0; i < R; ++i) {
            grid[i] = inf.readLine("[#.]{3,1000}", "row");
            ensuref((int)grid[i].size() == C,
                    "Row %d has length %d, expected %d", i, (int)grid[i].size(), C);
            for (char ch : grid[i])
                if (ch == '.') freeCount++;
        }

        // Build graph over free cells: each free cell is a node, edges to 4-neighbors
        const int dr[4] = {1, -1, 0, 0};
        const int dc[4] = {0, 0, 1, -1};

        auto inside = [&](int r, int c) {
            return (0 <= r && r < R && 0 <= c && c < C);
        };

        // Check the free cells form a tree (or empty):
        //  - zero or one connected component
        //  - number of edges = freeCount - 1 (for freeCount > 0)
        if (freeCount > 0) {
            vector<vector<int>> vis(R, vector<int>(C, 0));

            // Find first free cell
            int sr = -1, sc = -1;
            for (int i = 0; i < R && sr == -1; ++i)
                for (int j = 0; j < C && sr == -1; ++j)
                    if (grid[i][j] == '.') {
                        sr = i; sc = j;
                    }

            // BFS to check connectivity and count edges
            queue<pair<int,int>> q;
            q.push({sr, sc});
            vis[sr][sc] = 1;
            long long visited = 0;
            long long undirectedEdges = 0;

            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                visited++;

                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (!inside(nr, nc)) continue;
                    if (grid[nr][nc] != '.') continue;

                    // Count undirected edges only once: direction (r,c) -> (nr,nc)
                    // where (nr, nc) > (r, c) in lexicographic order
                    if (nr > r || (nr == r && nc > c)) {
                        undirectedEdges++;
                    }

                    if (!vis[nr][nc]) {
                        vis[nr][nc] = 1;
                        q.push({nr, nc});
                    }
                }
            }

            ensuref(visited == freeCount,
                    "Free cells are not in a single connected component: visited %lld of %lld",
                    visited, freeCount);
            ensuref(undirectedEdges == freeCount - 1,
                    "Free-cell graph is not a tree: edges=%lld, free nodes=%lld (expected edges=%lld)",
                    undirectedEdges, freeCount, freeCount - 1);
        }

        // Optionally, we can also verify that the diameter exists and is within bounds.
        // Given constraints, maximum diameter is <= freeCount-1, which trivially holds
        // in a tree, so no extra numeric bound is necessary.

        // ensure strict formatting
        // next test case (if any) will continue from here
    }

    inf.readEof();
}
