#include "testlib.h"
#include <array>
#include <vector>
using namespace std;

static vector<int> shuffledRange(int n) {
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = i;
    }
    shuffle(values.begin(), values.end());
    return values;
}

static array<array<int, 9>, 9> makeSolvedGrid() {
    vector<int> bandOrder = shuffledRange(3);
    vector<int> stackOrder = shuffledRange(3);
    vector<int> rowOrder;
    vector<int> colOrder;

    for (int band : bandOrder) {
        vector<int> inside = shuffledRange(3);
        for (int r : inside) {
            rowOrder.push_back(band * 3 + r);
        }
    }

    for (int stack : stackOrder) {
        vector<int> inside = shuffledRange(3);
        for (int c : inside) {
            colOrder.push_back(stack * 3 + c);
        }
    }

    vector<int> digits = shuffledRange(9);
    array<array<int, 9>, 9> grid{};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int base = (rowOrder[i] * 3 + rowOrder[i] / 3 + colOrder[j]) % 9;
            grid[i][j] = digits[base] + 1;
        }
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    auto grid = makeSolvedGrid();
    vector<int> cells = shuffledRange(81);
    int mode = rnd.next(0, 4);
    int clues = 0;

    if (mode == 0) {
        clues = rnd.next(24, 32);
    } else if (mode == 1) {
        clues = rnd.next(33, 48);
    } else if (mode == 2) {
        clues = rnd.next(49, 72);
    } else if (mode == 3) {
        clues = 81;
    } else {
        clues = rnd.next(28, 45);
        for (int box = 0; box < 9; ++box) {
            int keep = rnd.next(1, 5);
            vector<int> boxCells;
            int br = (box / 3) * 3;
            int bc = (box % 3) * 3;
            for (int dr = 0; dr < 3; ++dr) {
                for (int dc = 0; dc < 3; ++dc) {
                    boxCells.push_back((br + dr) * 9 + (bc + dc));
                }
            }
            shuffle(boxCells.begin(), boxCells.end());
            for (int i = keep; i < 9; ++i) {
                grid[boxCells[i] / 9][boxCells[i] % 9] = 0;
            }
        }
    }

    if (mode != 4) {
        for (int i = clues; i < 81; ++i) {
            grid[cells[i] / 9][cells[i] % 9] = 0;
        }
    } else {
        vector<int> present;
        for (int idx = 0; idx < 81; ++idx) {
            if (grid[idx / 9][idx % 9] != 0) {
                present.push_back(idx);
            }
        }
        shuffle(present.begin(), present.end());
        for (int i = clues; i < int(present.size()); ++i) {
            grid[present[i] / 9][present[i] % 9] = 0;
        }
    }

    for (int i = 0; i < 9; ++i) {
        vector<int> row(grid[i].begin(), grid[i].end());
        println(row);
    }

    return 0;
}
