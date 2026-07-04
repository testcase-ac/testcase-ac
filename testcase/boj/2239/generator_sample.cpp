#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> digitMap(10);
    vector<int> digits = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(digits.begin(), digits.end());
    for (int i = 1; i <= 9; i++) {
        digitMap[i] = digits[i - 1];
    }

    vector<int> rowBands = {0, 1, 2};
    vector<int> colBands = {0, 1, 2};
    shuffle(rowBands.begin(), rowBands.end());
    shuffle(colBands.begin(), colBands.end());

    vector<int> rows;
    vector<int> cols;
    for (int band : rowBands) {
        vector<int> inside = {0, 1, 2};
        shuffle(inside.begin(), inside.end());
        for (int offset : inside) {
            rows.push_back(band * 3 + offset);
        }
    }
    for (int band : colBands) {
        vector<int> inside = {0, 1, 2};
        shuffle(inside.begin(), inside.end());
        for (int offset : inside) {
            cols.push_back(band * 3 + offset);
        }
    }

    vector<vector<int>> grid(9, vector<int>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int base = (rows[i] * 3 + rows[i] / 3 + cols[j]) % 9 + 1;
            grid[i][j] = digitMap[base];
        }
    }

    int mode = rnd.next(0, 4);
    int clues;
    if (mode == 0) {
        clues = rnd.next(25, 32);
    } else if (mode == 1) {
        clues = rnd.next(33, 45);
    } else if (mode == 2) {
        clues = rnd.next(46, 62);
    } else if (mode == 3) {
        clues = rnd.next(63, 80);
    } else {
        clues = 81;
    }

    vector<int> cells;
    if (mode == 1) {
        for (int b = 0; b < 9; b++) {
            vector<int> blockCells;
            int br = (b / 3) * 3;
            int bc = (b % 3) * 3;
            for (int di = 0; di < 3; di++) {
                for (int dj = 0; dj < 3; dj++) {
                    blockCells.push_back((br + di) * 9 + (bc + dj));
                }
            }
            shuffle(blockCells.begin(), blockCells.end());
            cells.insert(cells.end(), blockCells.begin(), blockCells.end());
        }
    } else if (mode == 2) {
        for (int diagonal = 0; diagonal <= 16; diagonal++) {
            vector<int> diagonalCells;
            for (int i = 0; i < 9; i++) {
                int j = diagonal - i;
                if (0 <= j && j < 9) {
                    diagonalCells.push_back(i * 9 + j);
                }
            }
            shuffle(diagonalCells.begin(), diagonalCells.end());
            cells.insert(cells.end(), diagonalCells.begin(), diagonalCells.end());
        }
    } else {
        for (int idx = 0; idx < 81; idx++) {
            cells.push_back(idx);
        }
        shuffle(cells.begin(), cells.end());
    }

    int blanks = 81 - clues;
    for (int k = 0; k < blanks; k++) {
        int idx = cells[k];
        grid[idx / 9][idx % 9] = 0;
    }

    for (int i = 0; i < 9; i++) {
        string row;
        for (int j = 0; j < 9; j++) {
            row.push_back(char('0' + grid[i][j]));
        }
        println(row);
    }

    return 0;
}
