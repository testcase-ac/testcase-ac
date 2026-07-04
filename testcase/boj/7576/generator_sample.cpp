#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using Grid = vector<vector<int>>;

static void printGrid(const Grid& grid) {
    int n = static_cast<int>(grid.size());
    int m = static_cast<int>(grid[0].size());
    println(m, n);
    for (const auto& row : grid) {
        println(row);
    }
}

static Grid fullGrid(int n, int m, int value) {
    return Grid(n, vector<int>(m, value));
}

static Grid randomGrid(int n, int m) {
    int emptyWeight = rnd.next(0, 5);
    int unripeWeight = rnd.next(1, 8);
    int ripeWeight = rnd.next(0, 4);
    int totalWeight = emptyWeight + unripeWeight + ripeWeight;

    Grid grid(n, vector<int>(m, 0));
    bool hasTomato = false;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            int pick = rnd.next(1, totalWeight);
            if (pick <= emptyWeight) {
                grid[r][c] = -1;
            } else if (pick <= emptyWeight + unripeWeight) {
                grid[r][c] = 0;
                hasTomato = true;
            } else {
                grid[r][c] = 1;
                hasTomato = true;
            }
        }
    }
    if (!hasTomato) {
        grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = rnd.next(0, 1);
    }
    return grid;
}

static Grid corridorGrid(int n, int m) {
    Grid grid = fullGrid(n, m, -1);
    vector<pair<int, int>> path;
    for (int r = 0; r < n; ++r) {
        if (r % 2 == 0) {
            for (int c = 0; c < m; ++c) path.push_back({r, c});
        } else {
            for (int c = m - 1; c >= 0; --c) path.push_back({r, c});
        }
    }

    int keep = rnd.next(max(2, min(n, m)), n * m);
    for (int i = 0; i < keep; ++i) {
        grid[path[i].first][path[i].second] = 0;
    }
    grid[path[0].first][path[0].second] = 1;
    return grid;
}

static Grid sealedIslandGrid(int n, int m) {
    Grid grid = randomGrid(n, m);
    for (int r = 0; r < n; ++r) {
        grid[r][m / 2] = -1;
    }
    int leftRow = rnd.next(0, n - 1);
    int rightRow = rnd.next(0, n - 1);
    grid[leftRow][rnd.next(0, max(0, m / 2 - 1))] = 1;
    grid[rightRow][rnd.next(m / 2 + 1, m - 1)] = 0;
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 18 : 10);
    int m = rnd.next(2, mode == 5 ? 18 : 10);

    Grid grid;
    if (mode == 0) {
        grid = fullGrid(n, m, 1);
        if (rnd.next(0, 2) == 0) {
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < m; ++c) {
                    if (rnd.next(0, 4) == 0) grid[r][c] = -1;
                }
            }
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = 1;
        }
    } else if (mode == 1) {
        grid = fullGrid(n, m, 0);
    } else if (mode == 2) {
        grid = fullGrid(n, m, 0);
        grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = 1;
    } else if (mode == 3) {
        grid = corridorGrid(n, m);
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        m = rnd.next(3, 10);
        grid = sealedIslandGrid(n, m);
    } else {
        grid = randomGrid(n, m);
    }

    printGrid(grid);
    return 0;
}
