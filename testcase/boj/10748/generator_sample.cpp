#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r = rnd.next(2, 10);
    int c = rnd.next(2, 10);
    int k = rnd.next(1, min(r * c, 12));
    vector<vector<int>> grid(r, vector<int>(c, 1));

    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = r * c;
        vector<int> values(k);
        iota(values.begin(), values.end(), 1);
        shuffle(values.begin(), values.end());
        int at = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = values[at++];
            }
        }
    } else if (mode == 2) {
        k = rnd.next(2, min(r * c, 6));
        for (int i = 0; i < r; ++i) {
            int rowColor = rnd.next(1, k);
            for (int j = 0; j < c; ++j) {
                grid[i][j] = rowColor;
            }
        }
    } else if (mode == 3) {
        k = rnd.next(2, min(r * c, 8));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = (i + j) % k + 1;
            }
        }
    } else if (mode == 4) {
        k = rnd.next(2, min(r * c, 10));
        int heavy = rnd.next(1, k);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = rnd.next(0, 99) < 70 ? heavy : rnd.next(1, k);
            }
        }
    } else {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = rnd.next(1, k);
            }
        }
    }

    if (mode != 0 && rnd.next(0, 3) == 0) {
        grid[0][0] = grid[r - 1][c - 1];
    }

    println(r, c, k);
    for (int i = 0; i < r; ++i) {
        println(grid[i]);
    }

    return 0;
}
