#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read grid
    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(N, 0, 1, "cell");
        inf.readEoln();
        for (int j = 0; j < N; j++) {
            grid[i][j] = row[j];
        }
    }

    // Check there are at least two islands
    vector<vector<bool>> seen(N, vector<bool>(N, false));
    int islands = 0;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 1 && !seen[i][j]) {
                // Start BFS/DFS to mark this island
                islands++;
                queue<pair<int,int>> q;
                q.push({i, j});
                seen[i][j] = true;
                while (!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d], ny = y + dy[d];
                        if (nx >= 0 && nx < N && ny >= 0 && ny < N
                            && grid[nx][ny] == 1 && !seen[nx][ny]) {
                            seen[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }

    ensuref(islands >= 2,
            "The input must contain at least two islands, found %d island(s)", islands);

    inf.readEof();
    return 0;
}
