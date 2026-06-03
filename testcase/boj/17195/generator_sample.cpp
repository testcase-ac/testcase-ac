#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 4);
    } else if (mode <= 3) {
        n = rnd.next(3, 9);
    } else {
        n = rnd.next(2, 14);
    }

    vector<string> grid(n, string(n, 'L'));
    char base = rnd.next(0, 1) ? 'R' : 'L';
    char other = base == 'R' ? 'L' : 'R';

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = base;
            }
        }
        if (rnd.next(0, 1)) {
            grid[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = other;
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = ((i + j) % 2 == 0) ? base : other;
            }
        }
    } else if (mode == 2) {
        vector<int> rowFlip(n), colFlip(n);
        for (int i = 0; i < n; ++i) rowFlip[i] = rnd.next(0, 1);
        for (int j = 0; j < n; ++j) colFlip[j] = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = (rowFlip[i] ^ colFlip[j]) ? other : base;
            }
        }
        int badRow = rnd.next(0, n - 1);
        int badCol = rnd.next(0, n - 1);
        grid[badRow][badCol] = grid[badRow][badCol] == 'R' ? 'L' : 'R';
    } else if (mode == 3) {
        int special = rnd.next(0, n - 1);
        bool rowMode = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rowMode ? (i == special ? other : base)
                                     : (j == special ? other : base);
            }
        }
    } else {
        int rWeight = rnd.next(1, 4);
        int lWeight = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.next(1, rWeight + lWeight) <= rWeight ? 'R' : 'L';
            }
        }
    }

    println(n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
