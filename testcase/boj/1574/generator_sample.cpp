#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r = rnd.next(1, 12);
    int c = rnd.next(1, 12);
    set<pair<int, int>> emptyCells;

    if (mode == 0) {
        if (rnd.next(0, 4) == 0) {
            r = rnd.next(20, 300);
            c = rnd.next(20, 300);
        }
    } else if (mode == 1) {
        r = rnd.next(1, 6);
        c = rnd.next(1, 6);
        for (int row = 1; row <= r; ++row) {
            for (int col = 1; col <= c; ++col) {
                emptyCells.insert({row, col});
            }
        }
    } else if (mode == 2) {
        int rowsToFill = rnd.next(1, r);
        vector<int> rows;
        for (int row = 1; row <= r; ++row) {
            rows.push_back(row);
        }
        shuffle(rows.begin(), rows.end());

        for (int i = 0; i < rowsToFill; ++i) {
            for (int col = 1; col <= c; ++col) {
                emptyCells.insert({rows[i], col});
            }
        }
    } else if (mode == 3) {
        int colsToFill = rnd.next(1, c);
        vector<int> cols;
        for (int col = 1; col <= c; ++col) {
            cols.push_back(col);
        }
        shuffle(cols.begin(), cols.end());

        for (int i = 0; i < colsToFill; ++i) {
            for (int row = 1; row <= r; ++row) {
                emptyCells.insert({row, cols[i]});
            }
        }
    } else if (mode == 4) {
        int diagonalLength = min(r, c);
        for (int i = 1; i <= diagonalLength; ++i) {
            emptyCells.insert({i, i});
        }
        emptyCells.insert({1, 1});
        emptyCells.insert({1, c});
        emptyCells.insert({r, 1});
        emptyCells.insert({r, c});

        int extras = rnd.next(0, min(20, r * c));
        while (extras-- > 0) {
            emptyCells.insert({rnd.next(1, r), rnd.next(1, c)});
        }
    } else {
        if (rnd.next(0, 3) == 0) {
            r = rnd.next(100, 300);
            c = rnd.next(100, 300);
        }

        int n = rnd.next(1, min(600, r * c));
        while ((int)emptyCells.size() < n) {
            emptyCells.insert({rnd.next(1, r), rnd.next(1, c)});
        }
    }

    while ((int)emptyCells.size() > 600) {
        emptyCells.erase(prev(emptyCells.end()));
    }

    vector<pair<int, int>> cells(emptyCells.begin(), emptyCells.end());
    shuffle(cells.begin(), cells.end());

    println(r, c, (int)cells.size());
    for (auto cell : cells) {
        println(cell.first, cell.second);
    }

    return 0;
}
