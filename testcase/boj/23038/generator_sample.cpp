#include "testlib.h"

#include <vector>
using namespace std;

const int UP = 1;
const int RIGHT = 2;
const int DOWN = 4;
const int LEFT = 8;

vector<int> validMasks() {
    return {0, UP | RIGHT, UP | RIGHT | DOWN, UP | LEFT,
            UP | DOWN | RIGHT, UP | DOWN | RIGHT | LEFT,
            UP | DOWN | LEFT, RIGHT | DOWN, RIGHT | DOWN | LEFT,
            DOWN | LEFT, LEFT | RIGHT, UP | DOWN};
}

bool fitsBoundary(int mask, int i, int j, int n, int m) {
    if (i == 0 && (mask & UP)) return false;
    if (j + 1 == m && (mask & RIGHT)) return false;
    if (i + 1 == n && (mask & DOWN)) return false;
    if (j == 0 && (mask & LEFT)) return false;
    return true;
}

void drawTile(vector<string>& board, int i, int j, int mask) {
    int r = 3 * i;
    int c = 3 * j;
    if (mask == 0) return;
    board[r + 1][c + 1] = '#';
    if (mask & UP) board[r][c + 1] = '#';
    if (mask & RIGHT) board[r + 1][c + 2] = '#';
    if (mask & DOWN) board[r + 2][c + 1] = '#';
    if (mask & LEFT) board[r + 1][c] = '#';
}

int randomMaskForCell(int i, int j, int n, int m, int mode) {
    vector<int> candidates;
    for (int mask : validMasks()) {
        if (!fitsBoundary(mask, i, j, n, m)) continue;
        if (mode == 1 && mask == 0) continue;
        if (mode == 2 && __builtin_popcount((unsigned)mask) > 2) continue;
        if (mode == 3 && mask != 0 && __builtin_popcount((unsigned)mask) < 3) continue;
        candidates.push_back(mask);
    }
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 4 ? 18 : 10);
    int m = rnd.next(2, mode == 4 ? 18 : 10);

    vector<string> board(3 * n, string(3 * m, '.'));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i + j) % 2 == 1) continue;

            int mask = 0;
            if (mode == 0) {
                mask = rnd.next(0, 4) == 0 ? 0 : randomMaskForCell(i, j, n, m, 1);
            } else if (mode == 4) {
                int pattern = (i / 2 + j / 2 + rnd.next(0, 2)) % 3;
                mask = randomMaskForCell(i, j, n, m, pattern == 0 ? 2 : 3);
            } else {
                mask = randomMaskForCell(i, j, n, m, mode);
            }
            drawTile(board, i, j, mask);
        }
    }

    println(n, m);
    for (const string& row : board) println(row);
    return 0;
}
