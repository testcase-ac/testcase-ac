#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std;

static bool isGoalState(const vector<string>& grid) {
    int n = int(grid.size());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool expected = (i == j || i + j == n - 1);
            if ((grid[i][j] == 'X') != expected) {
                return false;
            }
        }
    }
    return true;
}

static vector<string> goalGrid(int n) {
    vector<string> grid(n, string(n, '.'));
    for (int i = 0; i < n; ++i) {
        grid[i][i] = 'X';
        grid[i][n - 1 - i] = 'X';
    }
    return grid;
}

static vector<string> permutedGoalGrid(int n) {
    vector<int> rows(n), cols(n);
    iota(rows.begin(), rows.end(), 0);
    iota(cols.begin(), cols.end(), 0);

    do {
        shuffle(rows.begin(), rows.end());
        shuffle(cols.begin(), cols.end());
    } while (n == 3 && rows == vector<int>({0, 1, 2}) && cols == vector<int>({0, 1, 2}));

    vector<string> goal = goalGrid(n);
    vector<string> grid(n, string(n, '.'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = goal[rows[i]][cols[j]];
        }
    }
    if (isGoalState(grid)) {
        swap(grid[0], grid[1]);
    }
    return grid;
}

static vector<string> randomExactCountGrid(int n) {
    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cells.push_back({i, j});
        }
    }

    vector<string> grid(n, string(n, '.'));
    do {
        for (string& row : grid) {
            fill(row.begin(), row.end(), '.');
        }
        shuffle(cells.begin(), cells.end());
        for (int k = 0; k < 2 * n - 1; ++k) {
            grid[cells[k].first][cells[k].second] = 'X';
        }
    } while (isGoalState(grid));
    return grid;
}

static vector<string> lopsidedGrid(int n) {
    vector<string> grid(n, string(n, '.'));
    vector<pair<int, int>> cells;
    int heavyRows = rnd.next(1, min(n, 3));
    for (int i = 0; i < heavyRows; ++i) {
        for (int j = 0; j < n; ++j) {
            cells.push_back({i, j});
        }
    }
    for (int i = heavyRows; i < n; ++i) {
        cells.push_back({i, rnd.next(0, n - 1)});
    }
    shuffle(cells.begin(), cells.end());

    int placed = 0;
    for (auto [r, c] : cells) {
        if (grid[r][c] == 'X') {
            continue;
        }
        grid[r][c] = 'X';
        if (++placed == 2 * n - 1) {
            break;
        }
    }

    for (int i = 0; placed < 2 * n - 1 && i < n; ++i) {
        for (int j = 0; placed < 2 * n - 1 && j < n; ++j) {
            if (grid[i][j] == '.') {
                grid[i][j] = 'X';
                ++placed;
            }
        }
    }
    if (isGoalState(grid)) {
        swap(grid[0][0], grid[0][1]);
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(100) < 70 ? 3 : 5;

        vector<string> grid;
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            grid = permutedGoalGrid(n);
        } else if (mode == 1) {
            grid = randomExactCountGrid(n);
        } else {
            grid = lopsidedGrid(n);
        }

        println(n);
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
