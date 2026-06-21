#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int chooseK() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(1, 5);
    if (mode == 2) return rnd.next(6, 19);
    if (mode == 3) return rnd.next(20, 40);
    if (mode == 4) return rnd.next(1000, 1000000);
    return rnd.any(vector<int>{1, 19, 20, 999999, 1000000});
}

void setCell(vector<string>& grid, int r, int c) {
    grid[r][c] = '#';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int r = rnd.next(1, 20);
    int c = rnd.next(1, 20);
    int k = chooseK();
    vector<string> grid(r, string(c, '.'));

    if (mode == 0) {
        // Empty grid, allowed by the local validator and existing fixed case.
    } else if (mode == 1) {
        setCell(grid, rnd.next(0, r - 1), rnd.next(0, c - 1));
    } else if (mode == 2) {
        int cells = rnd.next(2, min(8, r * c));
        vector<int> positions;
        for (int i = 0; i < r * c; ++i) positions.push_back(i);
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < cells; ++i) {
            setCell(grid, positions[i] / c, positions[i] % c);
        }
    } else if (mode == 3) {
        int len = min(r, c);
        bool anti = rnd.next(0, 1);
        for (int i = 0; i < len; ++i) {
            int col = anti ? c - 1 - i : i;
            if (0 <= col && col < c) setCell(grid, i, col);
        }
    } else if (mode == 4) {
        bool horizontal = rnd.next(0, 1);
        if (horizontal) {
            int row = rnd.any(vector<int>{0, r - 1});
            for (int j = 0; j < c; ++j) {
                if (rnd.next(0, 99) < 75) setCell(grid, row, j);
            }
        } else {
            int col = rnd.any(vector<int>{0, c - 1});
            for (int i = 0; i < r; ++i) {
                if (rnd.next(0, 99) < 75) setCell(grid, i, col);
            }
        }
    } else if (mode == 5) {
        int h = rnd.next(1, r);
        int w = rnd.next(1, c);
        int top = rnd.next(0, r - h);
        int left = rnd.next(0, c - w);
        for (int i = top; i < top + h; ++i) {
            for (int j = left; j < left + w; ++j) {
                if (rnd.next(0, 99) < 85) setCell(grid, i, j);
            }
        }
    } else {
        int probability = rnd.any(vector<int>{10, 25, 45, 70});
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (rnd.next(0, 99) < probability) setCell(grid, i, j);
            }
        }
    }

    println(r, c, k);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
