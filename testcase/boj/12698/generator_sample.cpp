#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

static void placeEndpoints(vector<string>& grid) {
    vector<pair<int, int>> cells;
    int r = (int)grid.size();
    int c = (int)grid[0].size();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == '.') {
                cells.push_back({i, j});
            }
        }
    }

    shuffle(cells.begin(), cells.end());
    if ((int)cells.size() < 2) {
        grid.assign(1, string(2, '.'));
        cells = {{0, 0}, {0, 1}};
    }

    grid[cells[0].first][cells[0].second] = 'O';
    grid[cells[1].first][cells[1].second] = 'X';
}

static vector<string> makeOpenGrid() {
    int r = rnd.next(1, 15);
    int c = rnd.next(1, 15);
    if (r * c == 1) c = 2;

    vector<string> grid(r, string(c, '.'));
    placeEndpoints(grid);
    return grid;
}

static vector<string> makeLineGrid() {
    int r = rnd.next(0, 1) == 0 ? 1 : rnd.next(2, 15);
    int c = r == 1 ? rnd.next(2, 15) : 1;
    vector<string> grid(r, string(c, '.'));

    int walls = rnd.next(0, max(0, r * c - 2));
    vector<pair<int, int>> cells;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < walls; ++i) {
        grid[cells[i].first][cells[i].second] = '#';
    }

    placeEndpoints(grid);
    return grid;
}

static vector<string> makeRandomWalls() {
    int r = rnd.next(2, 15);
    int c = rnd.next(2, 15);
    int mode = rnd.next(0, 2);
    int wallPercent = mode == 0 ? rnd.next(10, 35) : rnd.next(45, 75);

    vector<string> grid(r, string(c, '.'));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (rnd.next(1, 100) <= wallPercent) {
                grid[i][j] = '#';
            }
        }
    }

    placeEndpoints(grid);
    return grid;
}

static vector<string> makeCorridors() {
    int r = rnd.next(5, 15);
    int c = rnd.next(5, 15);
    vector<string> grid(r, string(c, '#'));

    int row = rnd.next(0, r - 1);
    int col = rnd.next(0, c - 1);
    grid[row][col] = '.';

    int segments = rnd.next(4, 12);
    for (int seg = 0; seg < segments; ++seg) {
        int dir = rnd.next(0, 3);
        int steps = rnd.next(2, 8);
        for (int step = 0; step < steps; ++step) {
            if (dir == 0 && row > 0) --row;
            if (dir == 1 && row + 1 < r) ++row;
            if (dir == 2 && col > 0) --col;
            if (dir == 3 && col + 1 < c) ++col;
            grid[row][col] = '.';
        }
    }

    placeEndpoints(grid);
    return grid;
}

static vector<string> makeChambers() {
    int r = rnd.next(6, 15);
    int c = rnd.next(6, 15);
    vector<string> grid(r, string(c, '.'));

    for (int i = 1; i < r - 1; i += rnd.next(2, 4)) {
        for (int j = 0; j < c; ++j) {
            grid[i][j] = '#';
        }
        grid[i][rnd.next(0, c - 1)] = '.';
    }
    for (int j = 1; j < c - 1; j += rnd.next(2, 4)) {
        for (int i = 0; i < r; ++i) {
            if (rnd.next(1, 100) <= 75) {
                grid[i][j] = '#';
            }
        }
        grid[rnd.next(0, r - 1)][j] = '.';
    }

    placeEndpoints(grid);
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int testCount = 50;
    println(testCount);

    for (int caseIndex = 0; caseIndex < testCount; ++caseIndex) {
        int mode = caseIndex < 5 ? caseIndex : rnd.next(0, 4);
        vector<string> grid;

        if (mode == 0) {
            grid = makeOpenGrid();
        } else if (mode == 1) {
            grid = makeLineGrid();
        } else if (mode == 2) {
            grid = makeRandomWalls();
        } else if (mode == 3) {
            grid = makeCorridors();
        } else {
            grid = makeChambers();
        }

        println((int)grid.size(), (int)grid[0].size());
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
