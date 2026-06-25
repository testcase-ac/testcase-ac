#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

using Grid = vector<string>;

Grid makeGrid(int rows, int cols, char value = '0') {
    return Grid(rows, string(cols, value));
}

void addRandomNoise(Grid& grid, int count) {
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());
    for (int i = 0; i < count; ++i) {
        grid[rnd.next(rows)][rnd.next(cols)] = '1';
    }
}

Grid randomSparse(int rows, int cols) {
    Grid grid = makeGrid(rows, cols);
    int cells = rows * cols;
    int ones = rnd.next(0, min(cells, max(1, rows + cols)));
    addRandomNoise(grid, ones);
    return grid;
}

Grid randomDense(int rows, int cols) {
    Grid grid = makeGrid(rows, cols);
    int zeros = rnd.next(0, min(rows * cols, max(1, rows + cols)));
    fill(grid.begin(), grid.end(), string(cols, '1'));
    for (int i = 0; i < zeros; ++i) {
        grid[rnd.next(rows)][rnd.next(cols)] = '0';
    }
    return grid;
}

Grid diagonalMatching(int rows, int cols) {
    Grid grid = makeGrid(rows, cols);
    int limit = min(rows, cols);
    vector<int> columns(cols);
    for (int i = 0; i < cols; ++i) {
        columns[i] = i;
    }
    shuffle(columns.begin(), columns.end());
    for (int row = 0; row < limit; ++row) {
        grid[row][columns[row]] = '1';
    }
    addRandomNoise(grid, rnd.next(0, max(1, limit / 2)));
    return grid;
}

Grid rowColumnCoverTrap(int rows, int cols) {
    Grid grid = makeGrid(rows, cols);
    int activeRows = rnd.next(1, rows);
    int activeCols = rnd.next(1, cols);
    vector<int> rowOrder(rows), colOrder(cols);
    for (int i = 0; i < rows; ++i) {
        rowOrder[i] = i;
    }
    for (int j = 0; j < cols; ++j) {
        colOrder[j] = j;
    }
    shuffle(rowOrder.begin(), rowOrder.end());
    shuffle(colOrder.begin(), colOrder.end());

    for (int i = 0; i < activeRows; ++i) {
        for (int j = 0; j < activeCols; ++j) {
            if (rnd.next(100) < 75) {
                grid[rowOrder[i]][colOrder[j]] = '1';
            }
        }
    }

    if (rnd.next(2) == 0) {
        for (int i = 0; i < activeRows; ++i) {
            grid[rowOrder[i]][colOrder[rnd.next(activeCols)]] = '1';
        }
    } else {
        for (int j = 0; j < activeCols; ++j) {
            grid[rowOrder[rnd.next(activeRows)]][colOrder[j]] = '1';
        }
    }
    return grid;
}

Grid striped(int rows, int cols) {
    Grid grid = makeGrid(rows, cols);
    if (rnd.next(2) == 0) {
        for (int row = rnd.next(2); row < rows; row += rnd.next(2, 3)) {
            for (int col = 0; col < cols; ++col) {
                grid[row][col] = '1';
            }
        }
    } else {
        for (int col = rnd.next(2); col < cols; col += rnd.next(2, 3)) {
            for (int row = 0; row < rows; ++row) {
                grid[row][col] = '1';
            }
        }
    }
    addRandomNoise(grid, rnd.next(0, max(1, (rows + cols) / 3)));
    return grid;
}

Grid makeCase(int mode, int rows, int cols) {
    if (mode == 0) {
        return makeGrid(rows, cols);
    }
    if (mode == 1) {
        return makeGrid(rows, cols, '1');
    }
    if (mode == 2) {
        return randomSparse(rows, cols);
    }
    if (mode == 3) {
        return randomDense(rows, cols);
    }
    if (mode == 4) {
        return diagonalMatching(rows, cols);
    }
    if (mode == 5) {
        return rowColumnCoverTrap(rows, cols);
    }
    return striped(rows, cols);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(8, 20);
    println(testCount);
    for (int caseIndex = 0; caseIndex < testCount; ++caseIndex) {
        int rows;
        int cols;
        if (caseIndex < 3) {
            rows = rnd.next(1, 3);
            cols = rnd.next(1, 3);
        } else if (rnd.next(100) < 85) {
            rows = rnd.next(2, 12);
            cols = rnd.next(2, 12);
        } else {
            rows = rnd.next(13, 25);
            cols = rnd.next(13, 25);
        }

        int mode = rnd.next(0, 6);
        Grid grid = makeCase(mode, rows, cols);
        println(rows, cols);
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
