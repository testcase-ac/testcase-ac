#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static string randomRow(int m, int oneBias) {
    string row;
    for (int j = 0; j < m; ++j) {
        row += rnd.wnext(2, oneBias) == 1 ? '1' : '0';
    }
    return row;
}

static vector<string> makeGrid(int n, int m, char fill) {
    return vector<string>(n, string(m, fill));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 16);
    vector<string> grid;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
        grid = makeGrid(n, m, '0');
        int flips = rnd.next(1, n * m);
        for (int k = 0; k < flips; ++k) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, m - 1);
            grid[i][j] = grid[i][j] == '0' ? '1' : '0';
        }
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(1, 100);
        grid.push_back(randomRow(m, rnd.next(-3, 3)));
    } else if (mode == 2) {
        n = rnd.next(1, 100);
        m = 1;
        grid = makeGrid(n, m, '0');
        for (int i = 0; i < n; ++i) {
            grid[i][0] = rnd.next(0, 1) ? '1' : '0';
        }
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 16);
        grid = makeGrid(n, m, rnd.next(0, 1) ? '1' : '0');
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 16);
        grid = makeGrid(n, m, '0');
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (i + j + rnd.next(0, 1)) % 2 ? '1' : '0';
            }
        }
    } else if (mode == 5) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 16);
        grid = makeGrid(n, m, '0');
        vector<pair<int, int>> cells;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                    cells.push_back({i, j});
                }
            }
        }
        shuffle(cells.begin(), cells.end());
        int marked = rnd.next(1, (int)cells.size());
        for (int k = 0; k < marked; ++k) {
            grid[cells[k].first][cells[k].second] = '1';
        }
    } else {
        n = rnd.next(3, 20);
        m = rnd.next(3, 20);
        int oneBias = rnd.next(-4, 4);
        for (int i = 0; i < n; ++i) {
            grid.push_back(randomRow(m, oneBias));
        }
    }

    println(n, m);
    for (const string& row : grid) println(row);
    return 0;
}
