#include "testlib.h"
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N, Q
    int N = inf.readInt(2, 6, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 1000, "Q");
    inf.readEoln();

    int n = 1 << N;
    vector<vector<int>> A(n, vector<int>(n));

    // Read grid A[r][c]
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            A[r][c] = inf.readInt(0, 100, "A_rc");
            if (c + 1 < n) inf.readSpace();
        }
        inf.readEoln();
    }

    // Read Q integers L_i
    vector<int> L(Q);
    if (Q > 0) {
        for (int i = 0; i < Q; ++i) {
            L[i] = inf.readInt(0, N, "L_i");
            if (i + 1 < Q) inf.readSpace();
        }
        inf.readEoln();
    }

    // Now validate implied global properties by simulating the process.
    // Constraints are small (n <= 64, Q <= 1000), so direct simulation is fine.

    auto inBounds = [n](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < n;
    };

    vector<vector<int>> grid = A;
    vector<vector<int>> temp(n, vector<int>(n));

    for (int qi = 0; qi < Q; ++qi) {
        int Lq = L[qi];
        int sz = 1 << Lq;
        // 1) rotate all subgrids of size sz x sz by 90 degrees clockwise
        if (sz > 1) {
            for (int br = 0; br < n; br += sz) {
                for (int bc = 0; bc < n; bc += sz) {
                    // rotate subgrid [br..br+sz-1][bc..bc+sz-1]
                    for (int i = 0; i < sz; ++i) {
                        for (int j = 0; j < sz; ++j) {
                            temp[br + j][bc + sz - 1 - i] = grid[br + i][bc + j];
                        }
                    }
                }
            }
        } else {
            // sz == 1, rotation does nothing
            // copy grid to temp to keep step uniform if we want
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    temp[i][j] = grid[i][j];
        }

        grid.swap(temp);

        // 2) decrease ice for cells with fewer than 3 non-zero neighbors
        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};

        // mark cells to decrease
        vector<pair<int,int>> dec;
        dec.reserve(n * n);

        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] <= 0) continue;
                int cnt = 0;
                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (inBounds(nr, nc) && grid[nr][nc] > 0) ++cnt;
                }
                if (cnt < 3) dec.push_back({r, c});
            }
        }
        for (auto &p : dec) {
            int r = p.first, c = p.second;
            if (grid[r][c] > 0) --grid[r][c];
        }
    }

    // After all spells, compute:
    // 1) sum of remaining ice
    long long sumIce = 0;
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            sumIce += grid[r][c];

    // 2) size of the largest connected component of positive-ice cells
    int maxComp = 0;
    vector<vector<int>> vis(n, vector<int>(n, 0));
    static const int dr4[4] = {-1, 1, 0, 0};
    static const int dc4[4] = {0, 0, -1, 1};

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] > 0 && !vis[r][c]) {
                int sz = 0;
                queue<pair<int,int>> q;
                vis[r][c] = 1;
                q.push({r, c});
                while (!q.empty()) {
                    auto [cr, cc] = q.front();
                    q.pop();
                    ++sz;
                    for (int k = 0; k < 4; ++k) {
                        int nr = cr + dr4[k];
                        int nc = cc + dc4[k];
                        if (!inBounds(nr, nc)) continue;
                        if (!vis[nr][nc] && grid[nr][nc] > 0) {
                            vis[nr][nc] = 1;
                            q.push({nr, nc});
                        }
                    }
                }
                if (sz > maxComp) maxComp = sz;
            }
        }
    }

    // There is no explicit "answer always exists" type constraint aside from definitions,
    // so we only simulate to ensure no overflow or invalid behavior arose logically.

    inf.readEof();
}
