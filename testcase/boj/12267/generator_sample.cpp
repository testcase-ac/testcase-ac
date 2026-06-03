#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

using Grid = vector<vector<int>>;

Grid makeValidSudoku(int n) {
    int side = n * n;
    vector<int> symbols(side);
    iota(symbols.begin(), symbols.end(), 1);
    shuffle(symbols.begin(), symbols.end());

    vector<int> rows;
    vector<int> bands(n);
    iota(bands.begin(), bands.end(), 0);
    shuffle(bands.begin(), bands.end());
    for (int band : bands) {
        vector<int> inside(n);
        iota(inside.begin(), inside.end(), 0);
        shuffle(inside.begin(), inside.end());
        for (int offset : inside) {
            rows.push_back(band * n + offset);
        }
    }

    vector<int> cols;
    vector<int> stacks(n);
    iota(stacks.begin(), stacks.end(), 0);
    shuffle(stacks.begin(), stacks.end());
    for (int stack : stacks) {
        vector<int> inside(n);
        iota(inside.begin(), inside.end(), 0);
        shuffle(inside.begin(), inside.end());
        for (int offset : inside) {
            cols.push_back(stack * n + offset);
        }
    }

    Grid grid(side, vector<int>(side));
    for (int i = 0; i < side; ++i) {
        for (int j = 0; j < side; ++j) {
            int raw = (rows[i] * n + rows[i] / n + cols[j]) % side;
            grid[i][j] = symbols[raw];
        }
    }
    return grid;
}

void corrupt(Grid& grid, int n, int mode) {
    int side = n * n;
    if (mode == 0) {
        grid[rnd.next(side)][rnd.next(side)] = rnd.next(side + 1, 999);
    } else if (mode == 1) {
        int row = rnd.next(side);
        int c1 = rnd.next(side);
        int c2 = rnd.next(side);
        if (c1 == c2) {
            c2 = (c2 + 1) % side;
        }
        grid[row][c2] = grid[row][c1];
    } else if (mode == 2) {
        int col = rnd.next(side);
        int r1 = rnd.next(side);
        int r2 = rnd.next(side);
        if (r1 == r2) {
            r2 = (r2 + 1) % side;
        }
        grid[r2][col] = grid[r1][col];
    } else {
        int blockRow = rnd.next(n) * n;
        int blockCol = rnd.next(n) * n;
        int r1 = blockRow + rnd.next(n);
        int c1 = blockCol + rnd.next(n);
        int r2 = blockRow + rnd.next(n);
        int c2 = blockCol + rnd.next(n);
        if (r1 == r2 && c1 == c2) {
            c2 = blockCol + (c2 - blockCol + 1) % n;
        }
        grid[r2][c2] = grid[r1][c1];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = (tc == 0 ? rnd.next(3, 6) : rnd.any(vector<int>{3, 4, 5, 6}));
        Grid grid = makeValidSudoku(n);

        if (tc > 0 && rnd.next(100) < 70) {
            corrupt(grid, n, rnd.next(4));
        }

        println(n);
        for (const auto& row : grid) {
            println(row);
        }
    }

    return 0;
}
