#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

vector<Cell> rectangleLoop(int height, int width) {
    vector<Cell> cells;
    for (int c = 1; c + 1 < width; ++c) {
        cells.push_back({0, c});
    }
    for (int r = 1; r + 1 < height; ++r) {
        cells.push_back({r, width - 1});
    }
    for (int c = width - 2; c >= 1; --c) {
        cells.push_back({height - 1, c});
    }
    for (int r = height - 2; r >= 1; --r) {
        cells.push_back({r, 0});
    }
    return cells;
}

vector<Cell> diagonalLoop() {
    return {{0, 1}, {1, 0}, {1, 2}, {2, 1}};
}

bool canPlace(const vector<string>& grid, const vector<Cell>& shape, int top, int left) {
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();
    vector<vector<bool>> proposed(rows, vector<bool>(cols, false));

    for (Cell cell : shape) {
        int r = top + cell.first;
        int c = left + cell.second;
        if (r < 0 || rows <= r || c < 0 || cols <= c || grid[r][c] == '#') {
            return false;
        }
        proposed[r][c] = true;
    }

    for (Cell cell : shape) {
        int r = top + cell.first;
        int c = left + cell.second;
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr == 0 && dc == 0) {
                    continue;
                }
                int nr = r + dr;
                int nc = c + dc;
                if (0 <= nr && nr < rows && 0 <= nc && nc < cols && grid[nr][nc] == '#' && !proposed[nr][nc]) {
                    return false;
                }
            }
        }
    }

    return true;
}

void place(vector<string>& grid, const vector<Cell>& shape, int top, int left) {
    for (Cell cell : shape) {
        grid[top + cell.first][left + cell.second] = '#';
    }
}

void tryPlaceRandom(vector<string>& grid, const vector<Cell>& shape, int attempts) {
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();
    int shapeRows = 0;
    int shapeCols = 0;
    for (Cell cell : shape) {
        shapeRows = max(shapeRows, cell.first + 1);
        shapeCols = max(shapeCols, cell.second + 1);
    }
    if (shapeRows > rows || shapeCols > cols) {
        return;
    }

    for (int attempt = 0; attempt < attempts; ++attempt) {
        int top = rnd.next(0, rows - shapeRows);
        int left = rnd.next(0, cols - shapeCols);
        if (canPlace(grid, shape, top, left)) {
            place(grid, shape, top, left);
            return;
        }
    }
}

void ensureValid(const vector<string>& grid) {
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] != '#') {
                continue;
            }
            int neighbors = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) {
                        continue;
                    }
                    int nr = r + dr;
                    int nc = c + dc;
                    if (0 <= nr && nr < rows && 0 <= nc && nc < cols && grid[nr][nc] == '#') {
                        ++neighbors;
                    }
                }
            }
            ensuref(neighbors == 2, "black pixel at (%d, %d) has %d black neighbors", r + 1, c + 1, neighbors);
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int rows = rnd.next(1, 25);
    int cols = rnd.next(1, 25);
    vector<string> grid(rows, string(cols, '.'));

    if (mode == 0) {
        rows = rnd.next(1, 8);
        cols = rnd.next(1, 8);
        grid.assign(rows, string(cols, '.'));
    } else if (mode == 1) {
        rows = rnd.next(3, 18);
        cols = rnd.next(3, 18);
        grid.assign(rows, string(cols, '.'));
        int loops = rnd.next(1, 4);
        for (int i = 0; i < loops; ++i) {
            tryPlaceRandom(grid, diagonalLoop(), 80);
        }
    } else if (mode == 2) {
        rows = rnd.next(5, 25);
        cols = rnd.next(5, 25);
        grid.assign(rows, string(cols, '.'));
        int loops = rnd.next(1, 3);
        for (int i = 0; i < loops; ++i) {
            int height = rnd.next(3, min(10, rows));
            int width = rnd.next(3, min(10, cols));
            tryPlaceRandom(grid, rectangleLoop(height, width), 100);
        }
    } else if (mode == 3) {
        rows = rnd.next(9, 25);
        cols = rnd.next(9, 25);
        grid.assign(rows, string(cols, '.'));
        int outerHeight = rnd.next(7, rows);
        int outerWidth = rnd.next(7, cols);
        int outerTop = rnd.next(0, rows - outerHeight);
        int outerLeft = rnd.next(0, cols - outerWidth);
        place(grid, rectangleLoop(outerHeight, outerWidth), outerTop, outerLeft);

        int innerMaxHeight = outerHeight - 4;
        int innerMaxWidth = outerWidth - 4;
        if (innerMaxHeight >= 3 && innerMaxWidth >= 3) {
            int innerHeight = rnd.next(3, innerMaxHeight);
            int innerWidth = rnd.next(3, innerMaxWidth);
            int innerTop = rnd.next(outerTop + 2, outerTop + outerHeight - innerHeight - 2);
            int innerLeft = rnd.next(outerLeft + 2, outerLeft + outerWidth - innerWidth - 2);
            place(grid, rectangleLoop(innerHeight, innerWidth), innerTop, innerLeft);
        }
    } else {
        rows = rnd.next(10, 30);
        cols = rnd.next(10, 30);
        grid.assign(rows, string(cols, '.'));
        int loops = rnd.next(3, 8);
        for (int i = 0; i < loops; ++i) {
            if (rnd.next(0, 1) == 0) {
                tryPlaceRandom(grid, diagonalLoop(), 100);
            } else {
                int height = rnd.next(3, min(8, rows));
                int width = rnd.next(3, min(8, cols));
                tryPlaceRandom(grid, rectangleLoop(height, width), 100);
            }
        }
    }

    ensureValid(grid);
    println(rows, cols);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
