#include "testlib.h"
#include <array>
#include <vector>
using namespace std;

static bool solveSudoku(vector<array<int, 9>>& grid) {
    int bestI = -1;
    int bestJ = -1;
    int bestMask = 0;
    int bestCount = 10;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (grid[i][j] != 0) {
                continue;
            }

            int used[10] = {};
            for (int k = 0; k < 9; ++k) {
                used[grid[i][k]] = 1;
                used[grid[k][j]] = 1;
            }
            int boxI = (i / 3) * 3;
            int boxJ = (j / 3) * 3;
            for (int di = 0; di < 3; ++di) {
                for (int dj = 0; dj < 3; ++dj) {
                    used[grid[boxI + di][boxJ + dj]] = 1;
                }
            }

            int mask = 0;
            int count = 0;
            for (int v = 1; v <= 9; ++v) {
                if (!used[v]) {
                    mask |= 1 << v;
                    ++count;
                }
            }
            if (count == 0) {
                return false;
            }
            if (count < bestCount) {
                bestI = i;
                bestJ = j;
                bestMask = mask;
                bestCount = count;
            }
        }
    }

    if (bestI == -1) {
        return true;
    }

    for (int v = 1; v <= 9; ++v) {
        if ((bestMask & (1 << v)) == 0) {
            continue;
        }
        grid[bestI][bestJ] = v;
        if (solveSudoku(grid)) {
            grid[bestI][bestJ] = 0;
            return true;
        }
    }
    grid[bestI][bestJ] = 0;
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N = 9;
    vector<array<int, N>> grid(N);

    for (int i = 0; i < N; i++) {
        auto row = inf.readInts(N, 0, 9, "cell");
        inf.readEoln();
        for (int j = 0; j < N; j++) {
            grid[i][j] = row[j];
        }
    }

    for (int i = 0; i < N; i++) {
        array<int, N+1> pos;
        pos.fill(-1);
        for (int j = 0; j < N; j++) {
            int v = grid[i][j];
            if (v == 0) continue;
            if (pos[v] != -1) {
                ensuref(false,
                        "Duplicate value %d in row %d at columns %d and %d",
                        v, i+1, pos[v]+1, j+1);
            }
            pos[v] = j;
        }
    }

    for (int j = 0; j < N; j++) {
        array<int, N+1> pos;
        pos.fill(-1);
        for (int i = 0; i < N; i++) {
            int v = grid[i][j];
            if (v == 0) continue;
            if (pos[v] != -1) {
                ensuref(false,
                        "Duplicate value %d in column %d at rows %d and %d",
                        v, j+1, pos[v]+1, i+1);
            }
            pos[v] = i;
        }
    }

    for (int bi = 0; bi < 3; bi++) {
        for (int bj = 0; bj < 3; bj++) {
            array<int, N+1> pos;
            pos.fill(-1);
            for (int di = 0; di < 3; di++) {
                for (int dj = 0; dj < 3; dj++) {
                    int i = bi*3 + di;
                    int j = bj*3 + dj;
                    int v = grid[i][j];
                    if (v == 0) continue;
                    if (pos[v] != -1) {
                        int pi = bi*3 + pos[v]/3;
                        int pj = bj*3 + pos[v]%3;
                        ensuref(false,
                                "Duplicate value %d in 3x3 box at cells (%d,%d) and (%d,%d)",
                                v, pi+1, pj+1, i+1, j+1);
                    }
                    pos[v] = di*3 + dj;
                }
            }
        }
    }

    vector<array<int, N>> solved = grid;
    ensuref(solveSudoku(solved), "Sudoku board has no valid completion");

    inf.readEof();
    return 0;
}
