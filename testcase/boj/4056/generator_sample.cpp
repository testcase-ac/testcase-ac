#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

using Grid = vector<string>;

Grid makeSolvedGrid() {
    vector<int> bands = {0, 1, 2};
    vector<int> stacks = {0, 1, 2};
    shuffle(bands.begin(), bands.end());
    shuffle(stacks.begin(), stacks.end());

    vector<int> rows;
    vector<int> cols;
    for (int band : bands) {
        vector<int> inner = {0, 1, 2};
        shuffle(inner.begin(), inner.end());
        for (int offset : inner) {
            rows.push_back(band * 3 + offset);
        }
    }
    for (int stack : stacks) {
        vector<int> inner = {0, 1, 2};
        shuffle(inner.begin(), inner.end());
        for (int offset : inner) {
            cols.push_back(stack * 3 + offset);
        }
    }

    vector<char> digits = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    shuffle(digits.begin(), digits.end());

    Grid grid(9, string(9, '0'));
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            int baseValue = (rows[r] * 3 + rows[r] / 3 + cols[c]) % 9;
            grid[r][c] = digits[baseValue];
        }
    }
    return grid;
}

void eraseFiveCells(Grid& grid) {
    vector<int> cells;
    for (int i = 0; i < 81; ++i) {
        cells.push_back(i);
    }
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < 5; ++i) {
        grid[cells[i] / 9][cells[i] % 9] = '0';
    }
}

Grid makeConflictingGrid() {
    Grid grid = makeSolvedGrid();

    int r1 = rnd.next(0, 8);
    int c1 = rnd.next(0, 8);
    int c2 = rnd.next(0, 7);
    if (c2 >= c1) {
        ++c2;
    }
    grid[r1][c2] = grid[r1][c1];

    vector<int> candidates;
    for (int i = 0; i < 81; ++i) {
        int row = i / 9;
        int col = i % 9;
        if (row != r1 || (col != c1 && col != c2)) {
            candidates.push_back(i);
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (int i = 0; i < 5; ++i) {
        grid[candidates[i] / 9][candidates[i] % 9] = '0';
    }

    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        bool conflict = rnd.next(0, 4) == 0;
        Grid grid = conflict ? makeConflictingGrid() : makeSolvedGrid();
        if (!conflict) {
            eraseFiveCells(grid);
        }

        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
