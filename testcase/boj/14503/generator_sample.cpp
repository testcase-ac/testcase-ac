#include "testlib.h"
#include <vector>
#include <utility>

using namespace std;

using Grid = vector<vector<int>>;

void setBorderWalls(Grid& grid) {
    int n = (int)grid.size();
    int m = (int)grid[0].size();
    for (int i = 0; i < n; ++i) {
        grid[i][0] = 1;
        grid[i][m - 1] = 1;
    }
    for (int j = 0; j < m; ++j) {
        grid[0][j] = 1;
        grid[n - 1][j] = 1;
    }
}

vector<pair<int, int>> emptyCells(const Grid& grid) {
    vector<pair<int, int>> cells;
    int n = (int)grid.size();
    int m = (int)grid[0].size();
    for (int i = 1; i + 1 < n; ++i) {
        for (int j = 1; j + 1 < m; ++j) {
            if (grid[i][j] == 0) cells.push_back({i, j});
        }
    }
    return cells;
}

Grid randomRoom(int n, int m) {
    Grid grid(n, vector<int>(m, 0));
    setBorderWalls(grid);

    int wallPercent = rnd.next(5, 45);
    for (int i = 1; i + 1 < n; ++i) {
        for (int j = 1; j + 1 < m; ++j) {
            if (rnd.next(100) < wallPercent) grid[i][j] = 1;
        }
    }
    return grid;
}

Grid corridorRoom(int n, int m) {
    Grid grid(n, vector<int>(m, 1));
    int row = rnd.next(1, n - 2);
    int col = rnd.next(1, m - 2);
    grid[row][col] = 0;

    int steps = rnd.next(n + m, n * m);
    for (int s = 0; s < steps; ++s) {
        int dir = rnd.next(4);
        int nr = row + (dir == 2) - (dir == 0);
        int nc = col + (dir == 1) - (dir == 3);
        if (nr <= 0 || nr >= n - 1 || nc <= 0 || nc >= m - 1) continue;
        row = nr;
        col = nc;
        grid[row][col] = 0;

        if (rnd.next(100) < 25) {
            int side = rnd.next(4);
            int sr = row + (side == 2) - (side == 0);
            int sc = col + (side == 1) - (side == 3);
            if (sr > 0 && sr < n - 1 && sc > 0 && sc < m - 1) grid[sr][sc] = 0;
        }
    }
    return grid;
}

Grid patternedRoom(int n, int m) {
    Grid grid(n, vector<int>(m, 0));
    setBorderWalls(grid);

    int style = rnd.next(3);
    for (int i = 1; i + 1 < n; ++i) {
        for (int j = 1; j + 1 < m; ++j) {
            bool wall = false;
            if (style == 0) wall = (i + j + rnd.next(2)) % 3 == 0;
            if (style == 1) wall = (i % 2 == 0 && j % 3 != 1);
            if (style == 2) wall = (j % 2 == 0 && i % 3 != 1);
            if (wall && rnd.next(100) < 80) grid[i][j] = 1;
        }
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(3, 15);
    int m = rnd.next(3, 15);
    if (mode == 3 && rnd.next(100) < 30) {
        n = rnd.next(16, 30);
        m = rnd.next(16, 30);
    }

    Grid grid;
    if (mode == 0) {
        grid = randomRoom(n, m);
    } else if (mode == 1) {
        grid = corridorRoom(n, m);
    } else if (mode == 2) {
        grid = patternedRoom(n, m);
    } else {
        grid = randomRoom(n, m);
        for (int i = 1; i + 1 < n; ++i) {
            for (int j = 1; j + 1 < m; ++j) {
                if (rnd.next(100) < 20) grid[i][j] = 0;
            }
        }
    }

    vector<pair<int, int>> cells = emptyCells(grid);
    if (cells.empty()) {
        grid[n / 2][m / 2] = 0;
        cells.push_back({n / 2, m / 2});
    }

    pair<int, int> start = rnd.any(cells);
    int d = rnd.next(0, 3);

    println(n, m);
    println(start.first, start.second, d);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
