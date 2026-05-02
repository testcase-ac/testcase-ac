// AI가 쓴 코드에 W와 B가 뒤바뀌어서 절대 YES인 케이스가 안나옵니다;;
// 정상화했습니다

#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 8);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        bool unsolvable = (rnd.next(0, 3) == 0);
        int n, m;
        if (unsolvable) {
            // allow 1D or 2D
            int mode = rnd.next(0, 2);
            if (mode == 0) {
                n = 1; m = rnd.next(1, 8);
            } else if (mode == 1) {
                m = 1; n = rnd.next(1, 8);
            } else {
                n = rnd.next(2, 8);
                m = rnd.next(2, 8);
            }
            vector<string> grid(n, string(m, '.'));
            int maxColored = min(n * m, 10);
            int t = rnd.next(1, maxColored);
            vector<pair<int,int>> coords;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    coords.emplace_back(i, j);
            shuffle(coords.begin(), coords.end());
            for (int i = 0; i < t; i++) {
                int x = coords[i].first, y = coords[i].second;
                grid[x][y] = rnd.any(string("BW"));
            }
            // ensure B != 2*W
            int B = 0, W = 0;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) {
                    if (grid[i][j] == 'B') B++;
                    else if (grid[i][j] == 'W') W++;
                }
            if (B == 2 * W) {
                // flip one cell
                bool done = false;
                for (int i = 0; i < n && !done; i++)
                    for (int j = 0; j < m && !done; j++) {
                        if (grid[i][j] == 'B') {
                            grid[i][j] = 'W';
                            B--; W++;
                            done = true;
                        }
                    }
                if (!done) {
                    for (int i = 0; i < n && !done; i++)
                        for (int j = 0; j < m && !done; j++) {
                            if (grid[i][j] == 'W') {
                                grid[i][j] = 'B';
                                W--; B++;
                                done = true;
                            }
                        }
                }
            }
            println(n, m);
            for (int i = 0; i < n; i++)
                printf("%s\n", grid[i].c_str());
        } else {
            // solvable: build a valid tiling
            n = rnd.next(2, 8);
            m = rnd.next(2, 8);
            vector<string> grid(n, string(m, '.'));
            vector<vector<bool>> occ(n, vector<bool>(m, false));
            vector<pair<int,int>> d1 = {{0,1},{1,0},{0,-1},{-1,0}};
            vector<pair<int,int>> d2 = {{1,0},{0,-1},{-1,0},{0,1}};
            int maxPieces = (n * m) / 3;
            int want = rnd.next(1, min(maxPieces, 6));
            int placed = 0, attempts = 0;
            while (placed < want && attempts < 1000) {
                attempts++;
                int x = rnd.next(n), y = rnd.next(m);
                if (occ[x][y]) continue;
                int ori = rnd.next(0, 3);
                int x1 = x + d1[ori].first, y1 = y + d1[ori].second;
                int x2 = x + d2[ori].first, y2 = y + d2[ori].second;
                if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m) continue;
                if (x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) continue;
                if (occ[x1][y1] || occ[x2][y2]) continue;
                grid[x][y] = 'B';
                grid[x1][y1] = 'W';
                grid[x2][y2] = 'W';
                occ[x][y] = occ[x1][y1] = occ[x2][y2] = true;
                placed++;
            }
            if (placed == 0) {
                // force one piece
                grid[0][0] = 'B';
                grid[0][1] = 'W';
                grid[1][0] = 'W';
            }
            println(n, m);
            for (int i = 0; i < n; i++)
                printf("%s\n", grid[i].c_str());
        }
    }
    return 0;
}
