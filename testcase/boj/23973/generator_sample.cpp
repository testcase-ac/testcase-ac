#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

void addPoint(vector<string>& board, int r, int c) {
    if (0 <= r && r < (int)board.size() && 0 <= c &&
        c < (int)board[0].size()) {
        board[r][c] = '1';
    }
}

void addTargetRings(vector<string>& board, int centerR, int centerC) {
    vector<Point> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
        {0, 1},   {1, -1}, {1, 0},  {1, 1},
    };

    addPoint(board, centerR, centerC);
    for (int distance = 1; distance <= 9; ++distance) {
        Point dir = directions[(distance + rnd.next(8)) % 8];
        addPoint(board, centerR + dir.first * distance,
                 centerC + dir.second * distance);
    }
}

int countOnes(const vector<string>& board) {
    int result = 0;
    for (const string& row : board) {
        result += count(row.begin(), row.end(), '1');
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n = 1, m = 1;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(1, 3);
        m = rnd.next(10, 60);
    } else if (mode == 2) {
        n = rnd.next(10, 35);
        m = rnd.next(10, 35);
    } else if (mode == 3) {
        n = rnd.next(19, 45);
        m = rnd.next(19, 45);
    } else if (mode == 4) {
        n = rnd.next(8, 30);
        m = rnd.next(8, 30);
    } else if (mode == 5) {
        n = rnd.next(30, 120);
        m = rnd.next(30, 120);
    } else {
        n = rnd.next(1, 2500);
        m = rnd.next(1, 2500);
    }

    vector<string> board(n, string(m, '0'));

    if (mode == 0) {
        int ones = rnd.next(0, min(n * m, 5));
        vector<Point> cells;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                cells.push_back({r, c});
            }
        }
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < ones; ++i) {
            addPoint(board, cells[i].first, cells[i].second);
        }
    } else if (mode == 1) {
        int ones = rnd.next(1, min(n * m, 40));
        for (int i = 0; i < ones; ++i) {
            addPoint(board, rnd.next(n), rnd.next(m));
        }
    } else if (mode == 2) {
        int len = rnd.next(1, min(n, m));
        int startR = rnd.next(0, n - len);
        int startC = rnd.next(0, m - len);
        for (int i = 0; i < len; ++i) {
            addPoint(board, startR + i, startC + i);
            if (rnd.next(4) == 0 && startC + i + 1 < m) {
                addPoint(board, startR + i, startC + i + 1);
            }
        }
    } else if (mode == 3) {
        int centerR = rnd.next(9, n - 10);
        int centerC = rnd.next(9, m - 10);
        addTargetRings(board, centerR, centerC);

        int noise = rnd.next(0, 20);
        for (int i = 0; i < noise; ++i) {
            addPoint(board, rnd.next(n), rnd.next(m));
        }
    } else if (mode == 4) {
        int centerR = rnd.next(n);
        int centerC = rnd.next(m);
        addTargetRings(board, centerR, centerC);
    } else if (mode == 5) {
        double density = rnd.next(0.01, 0.12);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next() < density) {
                    addPoint(board, r, c);
                }
            }
        }
    } else {
        int ones = rnd.next(1, min(100000, n * m));
        vector<Point> cells;
        cells.reserve(min(ones * 2, n * m));
        while ((int)cells.size() < ones) {
            cells.push_back({rnd.next(n), rnd.next(m)});
        }
        for (const Point& cell : cells) {
            addPoint(board, cell.first, cell.second);
        }
    }

    while (countOnes(board) > 100000) {
        int r = rnd.next(n);
        int c = rnd.next(m);
        board[r][c] = '0';
    }

    println(n, m);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
