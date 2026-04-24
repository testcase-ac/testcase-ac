#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small grid dimensions
    int M = rnd.next(2, 10);
    int N = rnd.next(2, 10);

    // Hyper-parameter: obstacle density between 0.1 and 0.7
    double dens = 0.1 + rnd.next() * 0.6;

    vector<vector<int>> grid;
    pair<int,int> start, goal;

    // Regenerate until start->goal connectivity is guaranteed
    while (true) {
        // Build grid
        grid.assign(M, vector<int>(N, 0));
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = (rnd.next() < dens ? 1 : 0);
            }
        }

        // Collect free cells
        vector<pair<int,int>> freeCells;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                if (grid[i][j] == 0)
                    freeCells.emplace_back(i, j);

        if ((int)freeCells.size() < 2)
            continue;

        // Pick two distinct positions
        shuffle(freeCells.begin(), freeCells.end());
        start = freeCells[0];
        goal  = freeCells[1];

        // BFS to check reachability
        vector<vector<bool>> vis(M, vector<bool>(N, false));
        queue<pair<int,int>> q;
        vis[start.first][start.second] = true;
        q.push(start);
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0,  0};
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < M && ny >= 0 && ny < N
                    && !vis[nx][ny] && grid[nx][ny] == 0) {
                    vis[nx][ny] = true;
                    q.emplace(nx, ny);
                }
            }
        }
        if (vis[goal.first][goal.second])
            break;
        // otherwise retry
    }

    // Random start/end orientations: 1=E,2=W,3=S,4=N
    int dstart = rnd.next(1, 4);
    int dgoal  = rnd.next(1, 4);

    // Output the test case
    println(M, N);
    for (int i = 0; i < M; i++)
        println(grid[i]);
    // convert to 1-based indexing
    println(start.first + 1, start.second + 1, dstart);
    println(goal.first + 1,  goal.second + 1,  dgoal);

    return 0;
}
