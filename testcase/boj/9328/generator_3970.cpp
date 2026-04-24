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
        int h = rnd.next(2, 8);
        int w = rnd.next(2, 8);
        println(h, w);
        // Hyper-parameters for densities
        double pWall = rnd.next(0.0, 1.0);
        double pDoc  = rnd.next(0.0, 1.0 - pWall);
        double pDoor = rnd.next(0.0, 1.0 - pWall - pDoc);
        double pKey  = rnd.next(0.0, 1.0 - pWall - pDoc - pDoor);
        // Build grid
        vector<string> grid(h, string(w, '.'));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                double x = rnd.next();
                if (x < pWall) {
                    grid[i][j] = '*';
                } else if (x < pWall + pDoc) {
                    grid[i][j] = '$';
                } else if (x < pWall + pDoc + pDoor) {
                    // Random uppercase door from A..E
                    grid[i][j] = char('A' + rnd.next(0, 4));
                } else if (x < pWall + pDoc + pDoor + pKey) {
                    // Random lowercase key from a..e
                    grid[i][j] = char('a' + rnd.next(0, 4));
                } else {
                    grid[i][j] = '.';
                }
            }
        }
        // Ensure at least one entry point on the border (non-wall)
        vector<pair<int,int>> border;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (i == 0 || j == 0 || i == h-1 || j == w-1) {
                    border.emplace_back(i, j);
                }
            }
        }
        bool hasEntry = false;
        for (auto &p : border) {
            if (grid[p.first][p.second] != '*') {
                hasEntry = true;
                break;
            }
        }
        if (!hasEntry) {
            auto pick = border[rnd.next((int)border.size() - 1)];
            grid[pick.first][pick.second] = '.';
        }
        // Output the grid
        for (int i = 0; i < h; i++) {
            printf("%s\n", grid[i].c_str());
        }
        // Generate initial keys
        // 30% chance no keys
        if (rnd.next(0.0, 1.0) < 0.3) {
            println("0");
        } else {
            int maxKeys = 5;
            int k = rnd.next(1, maxKeys);
            vector<char> pool;
            for (int i = 0; i < 5; i++) pool.push_back(char('a' + i));
            shuffle(pool.begin(), pool.end());
            string keys;
            for (int i = 0; i < k; i++) keys.push_back(pool[i]);
            println(keys);
        }
    }
    return 0;
}
