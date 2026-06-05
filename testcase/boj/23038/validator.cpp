#include "testlib.h"

#include <set>
#include <string>
#include <vector>
using namespace std;

const int UP = 1;
const int RIGHT = 2;
const int DOWN = 4;
const int LEFT = 8;

int tileMask(const vector<string>& board, int i, int j) {
    int baseR = 3 * i;
    int baseC = 3 * j;
    int mask = 0;
    if (board[baseR][baseC + 1] == '#') mask |= UP;
    if (board[baseR + 1][baseC + 2] == '#') mask |= RIGHT;
    if (board[baseR + 2][baseC + 1] == '#') mask |= DOWN;
    if (board[baseR + 1][baseC] == '#') mask |= LEFT;
    return mask;
}

void validateTileShape(const vector<string>& board, int i, int j, int mask) {
    int baseR = 3 * i;
    int baseC = 3 * j;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            bool expected = false;
            if (r == 1 && c == 1) {
                expected = mask != 0;
            } else if (r == 0 && c == 1) {
                expected = (mask & UP) != 0;
            } else if (r == 1 && c == 2) {
                expected = (mask & RIGHT) != 0;
            } else if (r == 2 && c == 1) {
                expected = (mask & DOWN) != 0;
            } else if (r == 1 && c == 0) {
                expected = (mask & LEFT) != 0;
            }

            ensuref((board[baseR + r][baseC + c] == '#') == expected,
                    "invalid 3x3 tile at cell (%d, %d)", i + 1, j + 1);
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300, "N");
    inf.readSpace();
    int m = inf.readInt(2, 300, "M");
    inf.readEoln();

    vector<string> board(3 * n);
    string rowPattern = "[.#]{" + to_string(3 * m) + "}";
    for (int r = 0; r < 3 * n; ++r) {
        board[r] = inf.readLine(rowPattern, "row");
    }
    inf.readEof();

    set<int> validMasks = {0, UP | RIGHT, UP | RIGHT | DOWN, UP | LEFT,
                           UP | DOWN | RIGHT, UP | DOWN | RIGHT | LEFT,
                           UP | DOWN | LEFT, RIGHT | DOWN, RIGHT | DOWN | LEFT,
                           DOWN | LEFT, LEFT | RIGHT, UP | DOWN};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int mask = tileMask(board, i, j);
            ensuref(validMasks.count(mask) != 0, "unknown tile mask at cell (%d, %d)", i + 1, j + 1);
            validateTileShape(board, i, j, mask);

            if ((i + j) % 2 == 1) {
                ensuref(mask == 0, "erased chessboard cell (%d, %d) is not blank", i + 1, j + 1);
            } else {
                ensuref(!(i == 0 && (mask & UP)), "top boundary line at cell (%d, %d)", i + 1, j + 1);
                ensuref(!(j + 1 == m && (mask & RIGHT)), "right boundary line at cell (%d, %d)", i + 1, j + 1);
                ensuref(!(i + 1 == n && (mask & DOWN)), "bottom boundary line at cell (%d, %d)", i + 1, j + 1);
                ensuref(!(j == 0 && (mask & LEFT)), "left boundary line at cell (%d, %d)", i + 1, j + 1);
            }
        }
    }

    // The official sample permits erased cells whose visible neighbors would
    // not determine one of the listed box-drawing characters by themselves.
}
