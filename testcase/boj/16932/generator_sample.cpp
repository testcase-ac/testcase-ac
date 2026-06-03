#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);
    vector<vector<int>> grid(n, vector<int>(m, 0));

    if (mode == 0) {
        double p = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next() < p;
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (i + j + rnd.next(0, 1)) % 2;
            }
        }
    } else if (mode == 2) {
        int r1 = rnd.next(0, n - 1);
        int r2 = rnd.next(r1, n - 1);
        int c1 = rnd.next(0, m - 1);
        int c2 = rnd.next(c1, m - 1);
        for (int i = r1; i <= r2; ++i) {
            for (int j = c1; j <= c2; ++j) {
                grid[i][j] = 1;
            }
        }
        int extra = rnd.next(0, n * m / 4);
        while (extra--) {
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = 1;
        }
    } else if (mode == 3) {
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, m - 1);
        for (int j = 0; j < m; ++j) grid[row][j] = 1;
        for (int i = 0; i < n; ++i) grid[i][col] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next() < 0.20) grid[i][j] ^= 1;
            }
        }
    } else if (mode == 4) {
        int islands = rnd.next(2, min(8, n * m));
        for (int k = 0; k < islands; ++k) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, m - 1);
            int len = rnd.next(1, 5);
            for (int step = 0; step < len; ++step) {
                grid[i][j] = 1;
                int dir = rnd.next(0, 3);
                if (dir == 0 && i > 0) --i;
                if (dir == 1 && i + 1 < n) ++i;
                if (dir == 2 && j > 0) --j;
                if (dir == 3 && j + 1 < m) ++j;
            }
        }
    } else {
        fill(grid.begin(), grid.end(), vector<int>(m, 1));
        int holes = rnd.next(1, max(1, n * m / 3));
        while (holes--) {
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = 0;
        }
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.emplace_back(i, j);
        }
    }
    shuffle(cells.begin(), cells.end());

    int zeros = 0;
    int ones = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            zeros += grid[i][j] == 0;
            ones += grid[i][j] == 1;
        }
    }
    if (zeros == 0) {
        grid[cells[0].first][cells[0].second] = 0;
    }
    if (ones == 0) {
        grid[cells[0].first][cells[0].second] = 1;
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
