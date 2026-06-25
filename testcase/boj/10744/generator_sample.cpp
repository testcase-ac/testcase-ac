#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r = rnd.next(2, 8);
    int c = rnd.next(2, 8);

    if (mode == 4) {
        r = rnd.next(8, 16);
        c = rnd.next(8, 16);
    } else if (mode == 5) {
        if (rnd.next(0, 1) == 0) {
            r = rnd.next(2, 4);
            c = rnd.next(10, 28);
        } else {
            r = rnd.next(10, 28);
            c = rnd.next(2, 4);
        }
    }

    int cells = r * c;
    int k;
    vector<vector<int>> grid(r, vector<int>(c, 1));

    if (mode == 0) {
        k = rnd.next(1, min(cells, 4));
        int value = rnd.next(1, k);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = value;
                if (rnd.next(0, 4) == 0) grid[i][j] = rnd.next(1, k);
            }
        }
    } else if (mode == 1) {
        k = rnd.next(2, min(cells, 6));
        for (int i = 0; i < r; ++i) {
            int rowValue = rnd.next(1, k);
            for (int j = 0; j < c; ++j) {
                grid[i][j] = rowValue;
                if (rnd.next(0, 5) == 0) grid[i][j] = rnd.next(1, k);
            }
        }
    } else if (mode == 2) {
        k = rnd.next(2, min(cells, 8));
        int a = rnd.next(1, k);
        int b = rnd.next(1, k);
        while (b == a) b = rnd.next(1, k);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = ((i + j) % 2 == 0 ? a : b);
                if (rnd.next(0, 7) == 0) grid[i][j] = rnd.next(1, k);
            }
        }
    } else if (mode == 3) {
        k = rnd.next(3, min(cells, 12));
        int blockH = rnd.next(1, max(1, r / 2));
        int blockW = rnd.next(1, max(1, c / 2));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int blockId = (i / blockH + j / blockW) % k;
                grid[i][j] = blockId + 1;
                if (rnd.next(0, 6) == 0) grid[i][j] = rnd.next(1, k);
            }
        }
    } else if (mode == 4) {
        k = rnd.next(max(2, cells / 3), cells);
        vector<int> values(cells);
        iota(values.begin(), values.end(), 1);
        shuffle(values.begin(), values.end());
        for (int i = 0; i < cells; ++i) {
            int value = values[i];
            if (value > k) value = rnd.next(1, k);
            grid[i / c][i % c] = value;
        }
    } else {
        k = rnd.next(2, min(cells, 10));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int bias = (i < r / 2 ? 1 : k);
                grid[i][j] = rnd.next(0, 2) == 0 ? bias : rnd.next(1, k);
            }
        }
    }

    println(r, c, k);
    for (int i = 0; i < r; ++i) {
        println(grid[i]);
    }

    return 0;
}
