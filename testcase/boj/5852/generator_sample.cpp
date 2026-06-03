#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void putPath(vector<string>& grid, pair<int, int> from, pair<int, int> to) {
    int r = from.first;
    int c = from.second;

    while (r != to.first) {
        r += (to.first > r ? 1 : -1);
        if (grid[r][c] == '.') {
            grid[r][c] = 'S';
        }
    }
    while (c != to.second) {
        c += (to.second > c ? 1 : -1);
        if (grid[r][c] == '.') {
            grid[r][c] = 'S';
        }
    }
}

void printGrid(const vector<string>& grid) {
    println((int)grid.size(), (int)grid[0].size());
    for (const string& row : grid) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int islands = rnd.next(1, 15);
        int c = 2 * islands - 1;
        vector<string> grid(1, string(c, 'S'));
        for (int j = 0; j < c; j += 2) {
            grid[0][j] = 'X';
        }
        printGrid(grid);
        return 0;
    }

    int r = rnd.next(5, 15);
    int c = rnd.next(5, 15);
    vector<pair<int, int>> cells;
    for (int i = 1; i < r; i += 3) {
        for (int j = 1; j < c; j += 3) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    int maxIslands = min(15, (int)cells.size());
    int islands = rnd.next(1, maxIslands);
    if (mode == 1) {
        islands = min(maxIslands, rnd.next(2, 5));
    } else if (mode == 2) {
        islands = max(1, maxIslands - rnd.next(0, min(3, maxIslands - 1)));
    }

    vector<pair<int, int>> chosen(cells.begin(), cells.begin() + islands);
    vector<string> grid(r, string(c, '.'));

    for (auto [i, j] : chosen) {
        grid[i][j] = 'X';

        int shape = rnd.next(0, 3);
        if (shape == 1 && j + 1 < c) {
            grid[i][j + 1] = 'X';
        } else if (shape == 2 && i + 1 < r) {
            grid[i + 1][j] = 'X';
        } else if (shape == 3 && i + 1 < r && j + 1 < c) {
            grid[i][j + 1] = 'X';
            grid[i + 1][j] = 'X';
        }
    }

    if (mode == 3) {
        sort(chosen.begin(), chosen.end());
    } else {
        shuffle(chosen.begin(), chosen.end());
    }

    for (int i = 1; i < islands; ++i) {
        if (rnd.next(0, 1) == 0) {
            putPath(grid, chosen[i - 1], {chosen[i].first, chosen[i - 1].second});
            putPath(grid, {chosen[i].first, chosen[i - 1].second}, chosen[i]);
        } else {
            putPath(grid, chosen[i - 1], {chosen[i - 1].first, chosen[i].second});
            putPath(grid, {chosen[i - 1].first, chosen[i].second}, chosen[i]);
        }
    }

    if (mode == 4) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (grid[i][j] == '.' && rnd.next(0, 5) == 0) {
                    grid[i][j] = 'S';
                }
            }
        }
    }

    printGrid(grid);
    return 0;
}
