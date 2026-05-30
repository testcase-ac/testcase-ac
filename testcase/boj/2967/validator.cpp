#include "testlib.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Square {
    int r;
    int c;
    int side;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(1, 100, "R");
    inf.readSpace();
    int C = inf.readInt(1, 100, "C");
    inf.readEoln();

    vector<string> grid(R);
    vector<pair<int, int>> marked;
    vector<vector<int>> dots(R + 1, vector<int>(C + 1, 0));

    for (int i = 0; i < R; ++i) {
        grid[i] = inf.readToken("[.x]+", "row");
        ensuref((int)grid[i].size() == C,
                "row %d has length %d, expected %d", i + 1,
                (int)grid[i].size(), C);
        inf.readEoln();

        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'x') {
                marked.push_back({i, j});
            }
        }
    }

    inf.readEof();

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            dots[i + 1][j + 1] = dots[i + 1][j] + dots[i][j + 1] -
                                  dots[i][j] + (grid[i][j] == '.');
        }
    }

    auto dotCount = [&](int r1, int c1, int r2, int c2) {
        return dots[r2 + 1][c2 + 1] - dots[r1][c2 + 1] -
               dots[r2 + 1][c1] + dots[r1][c1];
    };

    auto isAllMarkedSquare = [&](int r, int c, int side) {
        return dotCount(r, c, r + side - 1, c + side - 1) == 0;
    };

    vector<Square> squares;
    for (int side = min(R, C); side >= 1; --side) {
        for (int r = 0; r + side <= R; ++r) {
            for (int c = 0; c + side <= C; ++c) {
                if (isAllMarkedSquare(r, c, side)) {
                    squares.push_back({r, c, side});
                }
            }
        }
    }

    auto inside = [](const Square& sq, int r, int c) {
        return sq.r <= r && r < sq.r + sq.side &&
               sq.c <= c && c < sq.c + sq.side;
    };

    auto hasAllMarkedSquareCovering = [&](int minR, int maxR, int minC, int maxC) {
        int needSide = max(maxR - minR + 1, maxC - minC + 1);
        for (int side = needSide; side <= min(R, C); ++side) {
            int firstR = max(0, maxR - side + 1);
            int lastR = min(minR, R - side);
            int firstC = max(0, maxC - side + 1);
            int lastC = min(minC, C - side);
            for (int r = firstR; r <= lastR; ++r) {
                for (int c = firstC; c <= lastC; ++c) {
                    if (isAllMarkedSquare(r, c, side)) {
                        return true;
                    }
                }
            }
        }
        return false;
    };

    bool exists = false;
    for (const Square& first : squares) {
        int minR = R, maxR = -1, minC = C, maxC = -1;
        for (const auto& cell : marked) {
            int r = cell.first;
            int c = cell.second;
            if (inside(first, r, c)) {
                continue;
            }
            minR = min(minR, r);
            maxR = max(maxR, r);
            minC = min(minC, c);
            maxC = max(maxC, c);
        }

        if (maxR == -1 || hasAllMarkedSquareCovering(minR, maxR, minC, maxC)) {
            exists = true;
            break;
        }
    }

    ensuref(exists, "marked cells cannot be represented by two square floor plans");
    return 0;
}
