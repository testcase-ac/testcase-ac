#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for grid size
    int N = rnd.next(3, 10);
    int M = rnd.next(3, 10);
    // Maximum islands limited by cells and problem cap 6
    int maxK = min(6, (N * M + 1) / 2);
    int K = rnd.next(2, maxK);

    // Directions for adjacency check
    vector<pair<int,int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    vector<vector<int>> grid;

    // Try placing K single-cell islands with no 4-dir adjacency
    while (true) {
        grid.assign(N, vector<int>(M, 0));
        bool success = true;
        for (int i = 0; i < K; i++) {
            bool placed = false;
            for (int t = 0; t < 100; t++) {
                int r = rnd.next(0, N - 1);
                int c = rnd.next(0, M - 1);
                if (grid[r][c] != 0) continue;
                bool ok = true;
                for (auto &d : dirs) {
                    int nr = r + d.first, nc = c + d.second;
                    if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != 0) {
                        ok = false; break;
                    }
                }
                if (!ok) continue;
                grid[r][c] = 1;
                placed = true;
                break;
            }
            if (!placed) {
                success = false;
                break;
            }
        }
        if (success) break;
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        println(grid[i]);
    return 0;
}
