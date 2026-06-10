#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

static vector<Cell> allCells(int n, int m) {
    vector<Cell> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.push_back({i, j});
        }
    }
    return cells;
}

static int countOpen(const vector<string>& grid) {
    int open = 0;
    for (const string& row : grid) {
        open += count(row.begin(), row.end(), '.');
    }
    return open;
}

static void ensureOpenCapacity(vector<string>& grid, int needOpen) {
    int n = grid.size();
    int m = grid[0].size();
    vector<Cell> blocked;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'X') {
                blocked.push_back({i, j});
            }
        }
    }

    shuffle(blocked.begin(), blocked.end());
    while (countOpen(grid) < needOpen) {
        Cell cell = blocked.back();
        blocked.pop_back();
        grid[cell.first][cell.second] = '.';
    }
}

static void placeSpecials(vector<string>& grid, int kCount) {
    int n = grid.size();
    int m = grid[0].size();
    vector<Cell> empty;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                empty.push_back({i, j});
            }
        }
    }

    shuffle(empty.begin(), empty.end());
    Cell start = empty.back();
    empty.pop_back();
    grid[start.first][start.second] = 'S';

    for (int i = 0; i < kCount; ++i) {
        Cell restaurant = empty.back();
        empty.pop_back();
        grid[restaurant.first][restaurant.second] = 'K';
    }
}

static vector<string> openMap(int n, int m, int kCount) {
    vector<string> grid(n, string(m, '.'));
    placeSpecials(grid, kCount);
    return grid;
}

static vector<string> randomWallMap(int n, int m, int kCount) {
    vector<string> grid(n, string(m, '.'));
    int wallPercent = rnd.next(10, 40);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (rnd.next(100) < wallPercent) {
                grid[i][j] = 'X';
            }
        }
    }

    int needOpen = kCount + 1;
    vector<Cell> cells = allCells(n, m);
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < needOpen; ++i) {
        grid[cells[i].first][cells[i].second] = '.';
    }

    placeSpecials(grid, kCount);
    return grid;
}

static vector<string> corridorMap(int n, int m, int kCount) {
    vector<string> grid(n, string(m, 'X'));
    int row = rnd.next(0, n - 1);
    int col = rnd.next(0, m - 1);

    for (int j = 0; j < m; ++j) {
        grid[row][j] = '.';
    }
    for (int i = 0; i < n; ++i) {
        grid[i][col] = '.';
    }

    for (int i = 0; i < n; ++i) {
        if (rnd.next(100) < 35) {
            int endCol = rnd.next(0, m - 1);
            for (int j = min(col, endCol); j <= max(col, endCol); ++j) {
                grid[i][j] = '.';
            }
        }
    }
    for (int j = 0; j < m; ++j) {
        if (rnd.next(100) < 35) {
            int endRow = rnd.next(0, n - 1);
            for (int i = min(row, endRow); i <= max(row, endRow); ++i) {
                grid[i][j] = '.';
            }
        }
    }

    ensureOpenCapacity(grid, kCount + 1);
    placeSpecials(grid, kCount);
    return grid;
}

static vector<string> separatedMap(int n, int m, int kCount) {
    vector<string> grid(n, string(m, '.'));
    if (rnd.next(2) == 0) {
        int wallRow = rnd.next(1, n - 2);
        grid[wallRow] = string(m, 'X');
    } else {
        int wallCol = rnd.next(1, m - 2);
        for (int i = 0; i < n; ++i) {
            grid[i][wallCol] = 'X';
        }
    }

    ensureOpenCapacity(grid, kCount + 1);
    vector<Cell> empty;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                empty.push_back({i, j});
            }
        }
    }
    shuffle(empty.begin(), empty.end());

    Cell start = empty.back();
    empty.pop_back();
    grid[start.first][start.second] = 'S';

    for (int placed = 0; placed < kCount; ++placed) {
        Cell restaurant = empty.back();
        empty.pop_back();
        grid[restaurant.first][restaurant.second] = 'K';
    }

    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(4, 12);
    int m = rnd.next(4, 12);
    int maxRestaurants = min(20, n * m - 1);
    int kCount;
    if (mode == 4) {
        kCount = rnd.next(1, min(4, maxRestaurants));
    } else {
        kCount = rnd.next(5, maxRestaurants);
    }

    vector<string> grid;
    if (mode == 0) {
        grid = openMap(n, m, kCount);
    } else if (mode == 1) {
        grid = randomWallMap(n, m, kCount);
    } else if (mode == 2) {
        grid = corridorMap(n, m, kCount);
    } else {
        grid = separatedMap(n, m, kCount);
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
