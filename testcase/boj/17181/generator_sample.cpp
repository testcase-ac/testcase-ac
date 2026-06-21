#include "testlib.h"
#include <vector>
using namespace std;

int consonant() {
    return rnd.next(0, 13);
}

int vowel() {
    return rnd.next(14, 34);
}

int anyCell() {
    return rnd.next(0, 34);
}

int biasedCell(int consonantPercent) {
    return rnd.next(1, 100) <= consonantPercent ? consonant() : vowel();
}

void printGrid(const vector<vector<int>>& grid) {
    println((int)grid.size(), (int)grid[0].size());
    for (const auto& row : grid) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    if (mode == 5) {
        n = rnd.next(35, 50);
        m = rnd.next(35, 50);
    } else {
        n = rnd.next(4, 12);
        m = rnd.next(4, 12);
    }

    vector<vector<int>> grid(n, vector<int>(m));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = anyCell();
            }
        }
    } else if (mode == 1) {
        int consonantPercent = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = biasedCell(consonantPercent);
            }
        }
    } else if (mode == 2) {
        int phase = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int state = (i + j + phase) % 3;
                grid[i][j] = state == 1 ? vowel() : consonant();
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next(1, 100) <= 75 ? vowel() : consonant();
            }
        }
        grid[0][0] = consonant();
        int r = 0;
        int c = 0;
        int state = 0;
        while (r != n - 1 || c != m - 1) {
            if (r == n - 1 || (c + 1 < m && rnd.next(0, 1) == 0)) {
                ++c;
            } else {
                ++r;
            }
            state = (state + 1) % 3;
            grid[r][c] = state == 1 ? vowel() : consonant();
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = biasedCell(70);
            }
        }
        if (rnd.next(0, 1) == 0) {
            grid[0][0] = vowel();
        } else {
            grid[n - 1][m - 1] = vowel();
        }
    } else {
        int consonantPercent = rnd.next(35, 65);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = biasedCell(consonantPercent);
            }
        }
    }

    printGrid(grid);
    return 0;
}
