#include "testlib.h"
using namespace std;

char dirFromTo(int r1, int c1, int r2, int c2) {
    if (r2 == r1 && c2 == c1 + 1) return 'R';
    if (r2 == r1 && c2 == c1 - 1) return 'L';
    if (r2 == r1 + 1 && c2 == c1) return 'D';
    if (r2 == r1 - 1 && c2 == c1) return 'U';
    // Should only be called for neighbors; fallback (shouldn't happen)
    return 'U';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int patternType = rnd.next(0, 5);

    int N = 1, M = 1;
    vector<string> B;
    vector< vector<int> > cost;

    if (patternType == 0) {
        // Type 0: fully random small grid
        N = rnd.next(1, 8);
        M = rnd.next(1, 8);
        B.assign(N, string(M, 'U'));
        cost.assign(N, vector<int>(M));
        string dirs = "UDLR";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                B[i][j] = rnd.any(dirs);
                cost[i][j] = rnd.next(1, 500);
            }
        }
    } else if (patternType == 1) {
        // Type 1: border big cycle, interior random, one very cheap border cell
        N = rnd.next(3, 8);
        M = rnd.next(3, 8);
        B.assign(N, string(M, 'U'));
        cost.assign(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                cost[i][j] = rnd.next(50, 500);

        // Create border cycle
        // Top row (0,0) -> (0,M-1)
        for (int c = 0; c < M - 1; ++c)
            B[0][c] = 'R';
        // Right column (0,M-1) -> (N-1,M-1)
        for (int r = 0; r < N - 1; ++r)
            B[r][M - 1] = 'D';
        // Bottom row (N-1,M-1) -> (N-1,0)
        for (int c = M - 1; c > 0; --c)
            B[N - 1][c] = 'L';
        // Left column (N-1,0) -> (0,0)
        for (int r = N - 1; r > 0; --r)
            B[r][0] = 'U';

        // Interior cells: random directions
        string dirs = "UDLR";
        for (int i = 1; i < N - 1; ++i) {
            for (int j = 1; j < M - 1; ++j) {
                B[i][j] = rnd.any(dirs);
            }
        }

        // Choose one border cell with very low cost
        vector<pair<int,int>> border;
        for (int j = 0; j < M; ++j) {
            border.push_back({0, j});
            border.push_back({N - 1, j});
        }
        for (int r = 1; r < N - 1; ++r) {
            border.push_back({r, 0});
            border.push_back({r, M - 1});
        }
        pair<int,int> cheapCell = rnd.any(border);
        cost[cheapCell.first][cheapCell.second] = 1;
    } else if (patternType == 2) {
        // Type 2: several 2-cycles with varied costs
        N = rnd.next(2, 8);
        M = rnd.next(2, 8);
        B.assign(N, string(M, 'U'));
        cost.assign(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                cost[i][j] = rnd.next(1, 500);

        vector<vector<bool>> used(N, vector<bool>(M, false));
        vector<pair<int,int>> cycleCells;

        int maxCycles = min(4, (N * M) / 2);
        int numCycles = rnd.next(1, maxCycles);

        string dirs = "UDLR";

        for (int cyc = 0; cyc < numCycles; ++cyc) {
            bool placed = false;
            for (int attempt = 0; attempt < 30 && !placed; ++attempt) {
                int r = rnd.next(0, N - 1);
                int c = rnd.next(0, M - 1);
                if (used[r][c]) continue;
                vector<pair<int,int>> neigh;
                if (r > 0 && !used[r - 1][c]) neigh.push_back({r - 1, c});
                if (r + 1 < N && !used[r + 1][c]) neigh.push_back({r + 1, c});
                if (c > 0 && !used[r][c - 1]) neigh.push_back({r, c - 1});
                if (c + 1 < M && !used[r][c + 1]) neigh.push_back({r, c + 1});
                if (neigh.empty()) continue;
                auto nb = rnd.any(neigh);
                int r2 = nb.first, c2 = nb.second;
                B[r][c] = dirFromTo(r, c, r2, c2);
                B[r2][c2] = dirFromTo(r2, c2, r, c);
                used[r][c] = used[r2][c2] = true;
                cycleCells.push_back({r, c});
                cycleCells.push_back({r2, c2});
                // costs: one cheap, one expensive
                bool firstCheap = rnd.next(0, 1);
                int cheap = rnd.next(1, 10);
                int expensive = rnd.next(100, 500);
                if (firstCheap) {
                    cost[r][c] = cheap;
                    cost[r2][c2] = expensive;
                } else {
                    cost[r][c] = expensive;
                    cost[r2][c2] = cheap;
                }
                placed = true;
            }
        }

        // Remaining cells: random directions (could form extra cycles)
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (!used[i][j]) {
                    B[i][j] = rnd.any(dirs);
                }
            }
        }
    } else if (patternType == 3) {
        // Type 3: acyclic paths leading outside (answer should be 0)
        N = rnd.next(1, 8);
        M = rnd.next(1, 8);
        B.assign(N, string(M, 'U'));
        cost.assign(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                cost[i][j] = rnd.next(1, 100);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (i == N - 1 && j == M - 1) {
                    // bottom-right: move outside
                    B[i][j] = rnd.any(string("RD"));
                } else if (i == N - 1) {
                    // bottom row: go right
                    B[i][j] = 'R';
                } else if (j == M - 1) {
                    // rightmost column: go down
                    B[i][j] = 'D';
                } else {
                    // move either right or down
                    B[i][j] = rnd.next(0, 1) ? 'R' : 'D';
                }
            }
        }
    } else if (patternType == 4) {
        // Type 4: 1D grid (row or column) with a 2-cycle
        bool row = rnd.next(0, 1);
        if (row) {
            N = 1;
            M = rnd.next(2, 8);
        } else {
            M = 1;
            N = rnd.next(2, 8);
        }
        B.assign(N, string(M, 'U'));
        cost.assign(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                cost[i][j] = rnd.next(1, 500);

        if (row) {
            int k = rnd.next(0, M - 2);
            // 2-cycle between (0,k) and (0,k+1)
            B[0][k] = 'R';
            B[0][k + 1] = 'L';
            // chain others towards the cycle, edges may point outside
            for (int j = 0; j < M; ++j) {
                if (j == k || j == k + 1) continue;
                if (j < k) B[0][j] = 'R';
                else B[0][j] = 'L';
            }
            // maybe force ends to exit outside
            if (rnd.next(0, 1)) B[0][0] = 'L';
            if (rnd.next(0, 1)) B[0][M - 1] = 'R';

            // costs for the 2-cycle
            int cheap = rnd.next(1, 10);
            int expensive = rnd.next(100, 500);
            if (rnd.next(0, 1)) {
                cost[0][k] = cheap;
                cost[0][k + 1] = expensive;
            } else {
                cost[0][k] = expensive;
                cost[0][k + 1] = cheap;
            }
        } else {
            int k = rnd.next(0, N - 2);
            // 2-cycle between (k,0) and (k+1,0)
            B[k][0] = 'D';
            B[k + 1][0] = 'U';
            for (int i = 0; i < N; ++i) {
                if (i == k || i == k + 1) continue;
                if (i < k) B[i][0] = 'D';
                else B[i][0] = 'U';
            }
            if (rnd.next(0, 1)) B[0][0] = 'U';
            if (rnd.next(0, 1)) B[N - 1][0] = 'D';

            int cheap = rnd.next(1, 10);
            int expensive = rnd.next(100, 500);
            if (rnd.next(0, 1)) {
                cost[k][0] = cheap;
                cost[k + 1][0] = expensive;
            } else {
                cost[k][0] = expensive;
                cost[k + 1][0] = cheap;
            }
        }
    } else if (patternType == 5) {
        // Type 5: multiple 2x2 cycles
        N = rnd.next(2, 8);
        M = rnd.next(2, 8);
        B.assign(N, string(M, 'U'));
        cost.assign(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                cost[i][j] = rnd.next(1, 500);

        vector<vector<bool>> assigned(N, vector<bool>(M, false));
        vector<pair<int,int>> cycleCells;

        // Fill 2x2 blocks with 4-cycles
        for (int r = 0; r + 1 < N; r += 2) {
            for (int c = 0; c + 1 < M; c += 2) {
                // (r,c) -> (r,c+1)
                B[r][c] = 'R';
                B[r][c + 1] = 'D';
                B[r + 1][c + 1] = 'L';
                B[r + 1][c] = 'U';
                assigned[r][c] = assigned[r][c + 1] = true;
                assigned[r + 1][c + 1] = assigned[r + 1][c] = true;

                // costs: one cheap per 4-cycle
                vector<pair<int,int>> block = {
                    {r, c}, {r, c + 1}, {r + 1, c + 1}, {r + 1, c}
                };
                auto cheapCell = rnd.any(block);
                int cheap = rnd.next(1, 5);
                int expensive = rnd.next(100, 500);
                for (auto &p : block) {
                    if (p == cheapCell) cost[p.first][p.second] = cheap;
                    else cost[p.first][p.second] = expensive;
                }
                // keep track of cycle cells
                for (auto &p : block) cycleCells.push_back(p);
            }
        }

        // Remaining cells: random directions
        string dirs = "UDLR";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (!assigned[i][j]) {
                    B[i][j] = rnd.any(dirs);
                }
            }
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i)
        println(B[i]);
    for (int i = 0; i < N; ++i)
        println(cost[i]);

    return 0;
}
