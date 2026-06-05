#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

vector<Cell> allCells() {
    vector<Cell> cells;
    for (int row = 1; row <= 8; ++row) {
        for (int column = 1; column <= 8; ++column) {
            cells.emplace_back(column, row);
        }
    }
    return cells;
}

vector<Cell> randomSubset(int pieces) {
    vector<Cell> cells = allCells();
    shuffle(cells.begin(), cells.end());
    cells.resize(pieces);
    return cells;
}

vector<Cell> concentratedRow(int pieces) {
    vector<Cell> cells;
    int row = rnd.next(1, 8);
    vector<int> columns;
    for (int column = 1; column <= 8; ++column) {
        columns.push_back(column);
    }
    shuffle(columns.begin(), columns.end());

    int onTargetRow = min(pieces, rnd.next(1, 8));
    for (int i = 0; i < onTargetRow; ++i) {
        cells.emplace_back(columns[i], row);
    }

    vector<Cell> remaining;
    for (int otherRow = 1; otherRow <= 8; ++otherRow) {
        if (otherRow == row) {
            continue;
        }
        for (int column = 1; column <= 8; ++column) {
            remaining.emplace_back(column, otherRow);
        }
    }
    shuffle(remaining.begin(), remaining.end());
    while ((int)cells.size() < pieces) {
        cells.push_back(remaining.back());
        remaining.pop_back();
    }

    shuffle(cells.begin(), cells.end());
    return cells;
}

vector<Cell> balancedRows(int pieces) {
    vector<Cell> cells;
    vector<int> columnsByRow[9];
    for (int row = 1; row <= 8; ++row) {
        for (int column = 1; column <= 8; ++column) {
            columnsByRow[row].push_back(column);
        }
        shuffle(columnsByRow[row].begin(), columnsByRow[row].end());
    }

    int nextRow = rnd.next(1, 8);
    while ((int)cells.size() < pieces) {
        for (int tries = 0; tries < 8 && columnsByRow[nextRow].empty(); ++tries) {
            nextRow = nextRow % 8 + 1;
        }
        if (!columnsByRow[nextRow].empty()) {
            cells.emplace_back(columnsByRow[nextRow].back(), nextRow);
            columnsByRow[nextRow].pop_back();
        }
        nextRow = nextRow % 8 + 1;
    }

    shuffle(cells.begin(), cells.end());
    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int boards = rnd.next(1, 12);
    println(boards);

    for (int tc = 0; tc < boards; ++tc) {
        int mode = rnd.next(0, 4);
        int pieces = 0;
        vector<Cell> cells;

        if (mode == 0) {
            pieces = rnd.next(0, 3);
            cells = randomSubset(pieces);
        } else if (mode == 1) {
            pieces = rnd.next(1, 16);
            cells = concentratedRow(pieces);
        } else if (mode == 2) {
            pieces = rnd.next(8, 32);
            cells = balancedRows(pieces);
        } else if (mode == 3) {
            pieces = 64;
            cells = randomSubset(pieces);
        } else {
            pieces = rnd.next(1, 64);
            cells = randomSubset(pieces);
        }

        printf("%d", pieces);
        for (Cell cell : cells) {
            printf(" %d %d", cell.first, cell.second);
        }
        printf("\n");
    }

    return 0;
}
