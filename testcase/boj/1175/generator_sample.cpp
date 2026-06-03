#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

static vector<Cell> allCells(int n, int m) {
    vector<Cell> cells;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            cells.push_back({r, c});
        }
    }
    return cells;
}

static void placeSpecials(vector<string>& grid) {
    int n = int(grid.size());
    int m = int(grid[0].size());
    vector<Cell> free_cells;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == '.') {
                free_cells.push_back({r, c});
            }
        }
    }

    shuffle(free_cells.begin(), free_cells.end());
    grid[free_cells[0].first][free_cells[0].second] = 'S';
    grid[free_cells[1].first][free_cells[1].second] = 'C';
    grid[free_cells[2].first][free_cells[2].second] = 'C';
}

static vector<string> openRoom(int n, int m) {
    vector<string> grid(n, string(m, '.'));
    int wall_count = rnd.next(0, max(0, n * m / 4));
    vector<Cell> cells = allCells(n, m);
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < wall_count && i + 3 < int(cells.size()); ++i) {
        grid[cells[i].first][cells[i].second] = '#';
    }
    return grid;
}

static vector<string> corridor(int n, int m) {
    vector<string> grid(n, string(m, '#'));
    if (n == 1 || m == 1) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                grid[r][c] = '.';
            }
        }
        return grid;
    }

    int row = rnd.next(0, n - 1);
    for (int c = 0; c < m; ++c) {
        grid[row][c] = '.';
    }
    for (int c = 0; c < m; c += rnd.next(2, 4)) {
        int lo = min(row, rnd.next(0, n - 1));
        int hi = max(row, rnd.next(0, n - 1));
        for (int r = lo; r <= hi; ++r) {
            grid[r][c] = '.';
        }
    }
    return grid;
}

static vector<string> striped(int n, int m) {
    vector<string> grid(n, string(m, '.'));
    bool vertical = rnd.next(0, 1);
    if (vertical) {
        for (int c = rnd.next(0, 1); c < m; c += 2) {
            for (int r = 0; r < n; ++r) {
                if (rnd.next(0, 4) != 0) {
                    grid[r][c] = '#';
                }
            }
        }
    } else {
        for (int r = rnd.next(0, 1); r < n; r += 2) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next(0, 4) != 0) {
                    grid[r][c] = '#';
                }
            }
        }
    }
    return grid;
}

static vector<string> sparseNoise(int n, int m) {
    vector<string> grid(n, string(m, '.'));
    int threshold = rnd.next(10, 45);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (rnd.next(0, 99) < threshold) {
                grid[r][c] = '#';
            }
        }
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n, m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(3, 18);
    } else if (mode == 1) {
        n = rnd.next(3, 18);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 6);
        m = rnd.next(8, 24);
    } else {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    }

    vector<string> grid;
    if (mode == 0 || mode == 1) {
        grid = corridor(n, m);
    } else if (mode == 2) {
        grid = striped(n, m);
    } else if (mode == 3) {
        grid = sparseNoise(n, m);
    } else {
        grid = openRoom(n, m);
    }

    int free_count = 0;
    for (const string& row : grid) {
        free_count += int(count(row.begin(), row.end(), '.'));
    }
    if (free_count < 3) {
        grid = openRoom(n, m);
    }

    placeSpecials(grid);

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
