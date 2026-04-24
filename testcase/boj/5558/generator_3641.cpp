#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size hyper-parameters
    int H = rnd.next(3, 10);
    int W = rnd.next(3, 10);
    int maxN = min(9, H * W - 2);
    int N = rnd.next(1, maxN);

    // Obstacle density hyper-parameter: bias low, mid, or high
    vector<int> ts = {-1, 0, 1};
    int t = rnd.any(ts);
    int densInt = rnd.wnext(61, t); // in [0,60]
    double dens = densInt / 100.0;  // obstacle probability in [0.0,0.6]

    // Prepare cell list and assign special cells
    vector<pair<int,int>> cells;
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());

    pair<int,int> spos = cells[0];
    vector<pair<int,int>> cheesePos(N);
    for (int k = 0; k < N; k++) {
        cheesePos[k] = cells[1 + k];
    }
    // The rest are free for obstacles/empty
    vector<pair<int,int>> freePos(cells.begin() + 1 + N, cells.end());

    vector<string> grid;
    // Repeat until all cheeses reachable from start
    while (true) {
        grid.assign(H, string(W, '.'));
        // Place start
        grid[spos.first][spos.second] = 'S';
        // Place cheeses with numbers '1'..'N'
        for (int k = 0; k < N; k++) {
            auto [x, y] = cheesePos[k];
            grid[x][y] = char('1' + k);
        }
        // Fill obstacles randomly on free cells
        for (auto &p : freePos) {
            if (rnd.next() < dens) {
                grid[p.first][p.second] = 'X';
            }
        }
        // BFS to check reachability of all cheeses
        vector<vector<bool>> seen(H, vector<bool>(W, false));
        queue<pair<int,int>> q;
        q.push(spos);
        seen[spos.first][spos.second] = true;
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            const int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < H && ny >= 0 && ny < W
                    && !seen[nx][ny] && grid[nx][ny] != 'X') {
                    seen[nx][ny] = true;
                    q.emplace(nx, ny);
                }
            }
        }
        bool ok = true;
        for (auto &p : cheesePos) {
            if (!seen[p.first][p.second]) {
                ok = false;
                break;
            }
        }
        if (ok) break;
        // else retry obstacle placement
    }

    // Output
    println(H, W, N);
    for (int i = 0; i < H; i++) {
        println(grid[i]);
    }
    return 0;
}
