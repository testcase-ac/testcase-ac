#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

void carveRect(vector<string>& grid, int r1, int c1, int r2, int c2) {
    for (int r = r1; r <= r2; ++r) {
        for (int c = c1; c <= c2; ++c) {
            grid[r][c] = '0';
        }
    }
}

vector<Point> openCells(const vector<string>& grid) {
    vector<Point> cells;
    int n = (int)grid.size();
    for (int r = 1; r + 1 < n; ++r) {
        for (int c = 1; c + 1 < n; ++c) {
            if (grid[r][c] == '0') {
                cells.push_back({r, c});
            }
        }
    }
    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(mode == 3 ? 5 : 4, 12);
    vector<string> grid(n, string(n, '1'));

    if (mode == 0) {
        carveRect(grid, 1, 1, n - 2, n - 2);
        for (int r = 1; r + 1 < n; ++r) {
            for (int c = 1; c + 1 < n; ++c) {
                if (rnd.next(100) < 18) {
                    grid[r][c] = '1';
                }
            }
        }
        int corridorRow = rnd.next(1, n - 2);
        int corridorCol = rnd.next(1, n - 2);
        for (int c = 1; c + 1 < n; ++c) {
            grid[corridorRow][c] = '0';
        }
        for (int r = 1; r + 1 < n; ++r) {
            grid[r][corridorCol] = '0';
        }
    } else if (mode == 1) {
        int row = rnd.next(1, n - 2);
        int col = rnd.next(1, n - 2);
        for (int c = 1; c + 1 < n; ++c) {
            grid[row][c] = '0';
        }
        for (int r = 1; r + 1 < n; ++r) {
            grid[r][col] = '0';
        }
        for (int r = 1; r + 1 < n; ++r) {
            for (int c = 1; c + 1 < n; ++c) {
                if (rnd.next(100) < 25) {
                    grid[r][c] = '0';
                }
            }
        }
    } else if (mode == 2) {
        int split = rnd.next(2, n - 2);
        carveRect(grid, 1, 1, n - 2, split - 1);
        carveRect(grid, 1, split + 1, n - 2, n - 2);
    } else if (mode == 3) {
        int mid = rnd.next(2, n - 3);
        carveRect(grid, 1, 1, mid, mid);
        carveRect(grid, mid + 1, mid + 1, n - 2, n - 2);
        if (rnd.next(2) == 0) {
            grid[mid][mid + 1] = '0';
        }
    } else {
        int r = rnd.next(1, n - 2);
        int c = rnd.next(1, n - 2);
        grid[r][c] = '0';
        if (c + 1 < n - 1) {
            grid[r][c + 1] = '0';
        } else {
            grid[r][c - 1] = '0';
        }
    }

    vector<Point> cells = openCells(grid);
    shuffle(cells.begin(), cells.end());
    int m = rnd.next(1, min(10, (int)cells.size() - 1));

    Point start = cells.back();
    cells.pop_back();
    grid[start.first][start.second] = 'S';

    for (int i = 0; i < m; ++i) {
        Point key = cells.back();
        cells.pop_back();
        grid[key.first][key.second] = 'K';
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
