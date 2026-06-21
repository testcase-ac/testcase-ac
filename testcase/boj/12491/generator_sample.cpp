#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string> emptyGrid(int r, int c) {
    return vector<string>(r, string(c, '.'));
}

vector<string> randomGrid(int r, int c, int percentBlue) {
    vector<string> grid = emptyGrid(r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (rnd.next(100) < percentBlue) grid[i][j] = '#';
        }
    }
    return grid;
}

vector<string> tiledGrid(int r, int c) {
    vector<string> grid = emptyGrid(r, c);
    vector<pair<int, int>> blocks;
    for (int i = 0; i + 1 < r; ++i) {
        for (int j = 0; j + 1 < c; ++j) {
            blocks.push_back({i, j});
        }
    }
    shuffle(blocks.begin(), blocks.end());

    for (auto [i, j] : blocks) {
        if (rnd.next(100) >= 45) continue;
        bool free = true;
        for (int di = 0; di < 2; ++di) {
            for (int dj = 0; dj < 2; ++dj) {
                free &= grid[i + di][j + dj] == '.';
            }
        }
        if (!free) continue;
        for (int di = 0; di < 2; ++di) {
            for (int dj = 0; dj < 2; ++dj) {
                grid[i + di][j + dj] = '#';
            }
        }
    }
    return grid;
}

vector<string> checkerGrid(int r, int c) {
    vector<string> grid = emptyGrid(r, c);
    int parity = rnd.next(0, 1);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if ((i + j) % 2 == parity) grid[i][j] = '#';
        }
    }
    return grid;
}

vector<string> stripeGrid(int r, int c) {
    vector<string> grid = emptyGrid(r, c);
    bool horizontal = rnd.next(0, 1);
    if (horizontal) {
        int row = rnd.next(0, r - 1);
        for (int j = 0; j < c; ++j) grid[row][j] = '#';
    } else {
        int col = rnd.next(0, c - 1);
        for (int i = 0; i < r; ++i) grid[i][col] = '#';
    }
    return grid;
}

void disturbOneCell(vector<string>& grid) {
    int r = (int)grid.size();
    int c = (int)grid[0].size();
    int i = rnd.next(0, r - 1);
    int j = rnd.next(0, c - 1);
    grid[i][j] = grid[i][j] == '#' ? '.' : '#';
}

vector<string> makeCase() {
    int mode = rnd.next(0, 5);
    int r;
    int c;

    if (mode == 0) {
        r = rnd.next(1, 6);
        c = rnd.next(1, 6);
        return randomGrid(r, c, rnd.next(10, 85));
    }
    if (mode == 1) {
        r = rnd.next(2, 6);
        c = rnd.next(2, 6);
        return tiledGrid(r, c);
    }
    if (mode == 2) {
        r = rnd.next(1, 6);
        c = rnd.next(1, 6);
        return checkerGrid(r, c);
    }
    if (mode == 3) {
        r = rnd.next(1, 6);
        c = rnd.next(1, 6);
        return stripeGrid(r, c);
    }
    if (mode == 4) {
        r = rnd.next(2, 6);
        c = rnd.next(2, 6);
        vector<string> grid = tiledGrid(r, c);
        disturbOneCell(grid);
        return grid;
    }

    r = rnd.any(vector<int>{1, 2, 6});
    c = rnd.any(vector<int>{1, 2, 6});
    return randomGrid(r, c, rnd.any(vector<int>{0, 25, 50, 75, 100}));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 20);
    println(t);
    for (int caseIdx = 0; caseIdx < t; ++caseIdx) {
        vector<string> grid = makeCase();
        println((int)grid.size(), (int)grid[0].size());
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
