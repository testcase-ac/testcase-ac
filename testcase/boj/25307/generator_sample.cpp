#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using Cell = pair<int, int>;

int manhattan(Cell a, Cell b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<Cell> shuffledCells(int n, int m) {
    vector<Cell> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());
    return cells;
}

void printCase(int n, int m, int k, const vector<vector<int>>& grid) {
    println(n, m, k);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 9);
    int m = rnd.next(1, 9);
    int k = rnd.next(0, min(12, n + m));
    vector<vector<int>> grid(n, vector<int>(m, 0));
    vector<Cell> cells = shuffledCells(n, m);
    Cell start = cells.back();
    cells.pop_back();
    grid[start.first][start.second] = 4;

    if (mode == 0) {
        if (!cells.empty()) {
            Cell chair = cells.back();
            cells.pop_back();
            grid[chair.first][chair.second] = 2;
        }
    } else if (mode == 1) {
        int chairCount = min<int>(rnd.next(1, 3), cells.size());
        for (int i = 0; i < chairCount; ++i) {
            Cell c = cells.back();
            cells.pop_back();
            grid[c.first][c.second] = 2;
        }
        int pillarCount = min<int>(rnd.next(0, max(0, n * m / 4)), cells.size());
        for (int i = 0; i < pillarCount; ++i) {
            Cell c = cells.back();
            cells.pop_back();
            grid[c.first][c.second] = 1;
        }
    } else if (mode == 2) {
        k = rnd.next(1, min(12, n + m));
        if (!cells.empty()) {
            Cell mannequin = cells.back();
            cells.pop_back();
            grid[mannequin.first][mannequin.second] = 3;
        }
        int chairCount = min<int>(rnd.next(1, 3), cells.size());
        for (int i = 0; i < chairCount; ++i) {
            Cell c = cells.back();
            cells.pop_back();
            grid[c.first][c.second] = 2;
        }
    } else if (mode == 3) {
        if (n == 1 && m == 1) {
            k = rnd.next(0, 4000);
        } else {
            for (Cell c : cells) {
                if (c.first == start.first || c.second == start.second || rnd.next(0, 2) == 0) {
                    grid[c.first][c.second] = 1;
                }
            }
            vector<Cell> open;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (grid[i][j] == 0) {
                        open.push_back({i, j});
                    }
                }
            }
            if (!open.empty()) {
                Cell chair = rnd.any(open);
                grid[chair.first][chair.second] = 2;
            }
        }
    } else if (mode == 4) {
        k = 0;
        int fillCount = min<int>(rnd.next(0, max(0, n * m - 1)), cells.size());
        for (int i = 0; i < fillCount; ++i) {
            Cell c = cells.back();
            cells.pop_back();
            grid[c.first][c.second] = rnd.next(1, 3);
        }
    } else {
        n = rnd.next(8, 15);
        m = rnd.next(8, 15);
        k = rnd.next(0, 20);
        grid.assign(n, vector<int>(m, 0));
        cells = shuffledCells(n, m);
        start = cells.back();
        cells.pop_back();
        grid[start.first][start.second] = 4;

        for (Cell c : cells) {
            int d = manhattan(start, c);
            if (d <= 2 && rnd.next(0, 4) != 0) {
                continue;
            }
            int roll = rnd.next(0, 99);
            if (roll < 10) {
                grid[c.first][c.second] = 1;
            } else if (roll < 17) {
                grid[c.first][c.second] = 2;
            } else if (roll < 24) {
                grid[c.first][c.second] = 3;
            }
        }
    }

    printCase(n, m, k, grid);
    return 0;
}
