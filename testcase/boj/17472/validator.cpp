#include "testlib.h"
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();

    // Check product constraint
    long long prod = 1LL * N * M;
    ensuref(prod >= 3 && prod <= 100,
            "Product N*M must satisfy 3 ≤ N*M ≤ 100; got N=%d, M=%d, N*M=%lld",
            N, M, prod);

    // Read the grid
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(M, 0, 1, "grid_row");
        inf.readEoln();
        for (int j = 0; j < M; j++) {
            grid[i][j] = row[j];
        }
    }

    // Count islands (4-directional connected components of 1s)
    vector<vector<bool>> vis(N, vector<bool>(M, false));
    int islands = 0;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!vis[i][j] && grid[i][j] == 1) {
                // BFS to mark this component
                islands++;
                queue<pair<int,int>> q;
                q.push({i, j});
                vis[i][j] = true;
                while (!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                            if (!vis[nx][ny] && grid[nx][ny] == 1) {
                                vis[nx][ny] = true;
                                q.push({nx, ny});
                            }
                        }
                    }
                }
            }
        }
    }

    // Check number of islands constraint
    ensuref(islands >= 2 && islands <= 6,
            "Number of islands must be between 2 and 6; found %d",
            islands);

    inf.readEof();
    return 0;
}
