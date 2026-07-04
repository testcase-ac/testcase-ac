#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using Cell = pair<int, int>;

static void place(vector<string>& grid, Cell cell, char value) {
    grid[cell.first][cell.second] = value;
}

static vector<Cell> allCells(int r, int c) {
    vector<Cell> cells;
    cells.reserve(r * c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cells.emplace_back(i, j);
        }
    }
    return cells;
}

static int countChar(const vector<string>& grid, char value) {
    int count = 0;
    for (const string& row : grid) {
        count += (int)count_if(row.begin(), row.end(), [value](char ch) {
            return ch == value;
        });
    }
    return count;
}

static void ensureBothTypes(vector<string>& grid) {
    int r = (int)grid.size();
    int c = (int)grid[0].size();
    if (countChar(grid, 'M') == 0) {
        place(grid, {rnd.next(r), rnd.next(c)}, 'M');
    }
    if (countChar(grid, 'S') == 0) {
        vector<Cell> cells = allCells(r, c);
        shuffle(cells.begin(), cells.end());
        for (Cell cell : cells) {
            if (grid[cell.first][cell.second] != 'M') {
                place(grid, cell, 'S');
                return;
            }
        }
        place(grid, cells[0], 'S');
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int r;
    int c;

    if (mode == 0) {
        r = 1;
        c = rnd.next(2, 24);
    } else if (mode == 1) {
        r = rnd.next(2, 24);
        c = 1;
    } else if (mode == 2) {
        r = rnd.next(2, 7);
        c = rnd.next(2, 7);
    } else if (mode == 3) {
        r = rnd.next(6, 12);
        c = rnd.next(6, 12);
    } else {
        r = rnd.next(2, 10);
        c = rnd.next(2, 14);
    }

    vector<string> grid(r, string(c, '.'));
    vector<Cell> cells = allCells(r, c);
    shuffle(cells.begin(), cells.end());

    if (mode == 3) {
        vector<Cell> corners = {{0, 0}, {0, c - 1}, {r - 1, 0}, {r - 1, c - 1}};
        shuffle(corners.begin(), corners.end());
        for (int i = 0; i < (int)corners.size(); ++i) {
            place(grid, corners[i], i % 2 == 0 ? 'S' : 'M');
        }
    }

    int area = r * c;
    int targetSprinklers = rnd.next(1, max(1, area / 3));
    int targetMushrooms = rnd.next(1, max(1, area / 2));
    if (mode == 4) {
        targetSprinklers = rnd.next(1, max(1, area / 2));
        targetMushrooms = rnd.next(1, max(1, area / 2));
    }

    for (Cell cell : cells) {
        if (grid[cell.first][cell.second] != '.') {
            continue;
        }
        int sprinklers = countChar(grid, 'S');
        int mushrooms = countChar(grid, 'M');
        if (sprinklers < targetSprinklers && mushrooms < targetMushrooms) {
            place(grid, cell, rnd.next(2) == 0 ? 'S' : 'M');
        } else if (sprinklers < targetSprinklers) {
            place(grid, cell, 'S');
        } else if (mushrooms < targetMushrooms) {
            place(grid, cell, 'M');
        }
    }

    ensureBothTypes(grid);

    int d;
    if (mode <= 1) {
        d = rnd.next(1, max(r, c));
    } else if (mode == 2) {
        d = rnd.any(vector<int>{1, max(1, max(r, c) / 2), max(r, c)});
    } else {
        d = rnd.next(1, min(max(r, c), 5));
    }

    int sprinklerCount = countChar(grid, 'S');
    int k;
    if (rnd.next(3) == 0) {
        k = rnd.next(1, area);
    } else {
        k = rnd.next(1, max(1, sprinklerCount));
    }

    println(r, c, d, k);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
