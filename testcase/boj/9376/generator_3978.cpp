#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Small dimensions
        int h = rnd.next(2, 10);
        int w = rnd.next(2, 10);
        vector<string> grid;
        pair<int,int> p1, p2;
        // Retry until both prisoners can reach outside
        while (true) {
            // Hyper-parameters for density
            double wallProb = rnd.next() * 0.3;  // up to 30% walls
            double doorProb = rnd.next() * 0.5;  // up to 50% doors

            grid.assign(h, string(w, '.'));
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    double r = rnd.next();
                    if (r < wallProb) {
                        grid[i][j] = '*';
                    } else if (rnd.next() < doorProb) {
                        grid[i][j] = '#';
                    } else {
                        grid[i][j] = '.';
                    }
                }
            }
            // Collect empty cells for placing prisoners
            vector<pair<int,int>> empties;
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (grid[i][j] == '.') {
                        empties.emplace_back(i, j);
                    }
                }
            }
            if ((int)empties.size() < 2) continue;
            shuffle(empties.begin(), empties.end());
            p1 = empties[0];
            p2 = empties[1];
            grid[p1.first][p1.second] = '$';
            grid[p2.first][p2.second] = '$';
            // BFS from all border non-wall cells
            vector<vector<bool>> vis(h, vector<bool>(w, false));
            queue<pair<int,int>> q;
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (i == 0 || i == h-1 || j == 0 || j == w-1) {
                        if (grid[i][j] != '*') {
                            vis[i][j] = true;
                            q.emplace(i, j);
                        }
                    }
                }
            }
            int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                for (auto &d : dirs) {
                    int nx = x + d[0], ny = y + d[1];
                    if (nx >= 0 && nx < h && ny >= 0 && ny < w
                        && !vis[nx][ny] && grid[nx][ny] != '*') {
                        vis[nx][ny] = true;
                        q.emplace(nx, ny);
                    }
                }
            }
            // Check both prisoners can reach outside
            if (vis[p1.first][p1.second] && vis[p2.first][p2.second]) {
                break;
            }
        }
        // Output this test case
        println(h, w);
        for (int i = 0; i < h; i++) {
            println(grid[i]);
        }
    }
    return 0;
}
