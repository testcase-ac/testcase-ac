#include "testlib.h"
#include <vector>
#include <queue>
#include <string>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read R and C
    int R = inf.readInt(1, 100, "R");
    inf.readSpace();
    int C = inf.readInt(1, 100, "C");
    inf.readEoln();

    // 2. Read the grid
    vector<string> grid(R);
    for (int i = 0; i < R; ++i) {
        grid[i] = inf.readLine("[.#]{"+to_string(C)+","+to_string(C)+"}", "row");
        ensuref((int)grid[i].size() == C, "Row %d has length %d, expected %d", i+1, (int)grid[i].size(), C);
    }

    // 3. Check that no two clumps are adjacent
    //    - No two '#'s from different clumps are adjacent (orthogonally)
    //    - Each clump is either a single '#' or two '#'s side-by-side (orthogonally, not diagonal)
    //    - No two clumps are adjacent (orthogonally)
    //    - No clump is larger than 2 cells

    // We'll check this by:
    //   - Doing BFS/DFS for each '#' not yet visited
    //   - Each clump must be size 1 or 2
    //   - If size 2, must be orthogonally adjacent (not diagonal)
    //   - No two clumps are adjacent (orthogonally)

    vector<vector<bool>> vis(R, vector<bool>(C, false));
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == '#' && !vis[i][j]) {
                // Start a new clump
                vector<pair<int,int>> clump;
                queue<pair<int,int>> q;
                q.push({i,j});
                vis[i][j] = true;
                clump.push_back({i,j});

                while (!q.empty()) {
                    auto [r, c] = q.front(); q.pop();
                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                        if (grid[nr][nc] == '#' && !vis[nr][nc]) {
                            vis[nr][nc] = true;
                            q.push({nr, nc});
                            clump.push_back({nr, nc});
                        }
                    }
                }

                // Clump size must be 1 or 2
                ensuref(clump.size() == 1 || clump.size() == 2,
                    "Clump at (%d,%d) has size %d, but only size 1 or 2 allowed",
                    i+1, j+1, (int)clump.size());

                if (clump.size() == 2) {
                    // Must be orthogonally adjacent (not diagonal)
                    int r0 = clump[0].first, c0 = clump[0].second;
                    int r1 = clump[1].first, c1 = clump[1].second;
                    int drabs = abs(r0 - r1), dcabs = abs(c0 - c1);
                    ensuref((drabs == 1 && dcabs == 0) || (drabs == 0 && dcabs == 1),
                        "Clump of size 2 at (%d,%d) and (%d,%d) is not orthogonally adjacent",
                        r0+1, c0+1, r1+1, c1+1);
                }

                // For each cell in clump, check that all orthogonal neighbors are either '.'
                // or part of the same clump (i.e., not another '#')
                for (auto [r, c] : clump) {
                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                        if (grid[nr][nc] == '#') {
                            // If not part of this clump, it's an adjacent clump (invalid)
                            bool found = false;
                            for (auto [rr, cc] : clump) {
                                if (rr == nr && cc == nc) found = true;
                            }
                            ensuref(found, "Adjacent clumps detected at (%d,%d) and (%d,%d)",
                                    r+1, c+1, nr+1, nc+1);
                        }
                    }
                }
            }
        }
    }

    inf.readEof();
}
