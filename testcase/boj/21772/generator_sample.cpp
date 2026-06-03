#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int r;
    int c;
    if (mode == 0) {
        r = rnd.next(2, 4);
        c = rnd.next(2, 4);
    } else if (mode == 1) {
        r = rnd.next(5, 9);
        c = rnd.next(5, 9);
    } else if (mode == 2) {
        r = rnd.next(3, 7);
        c = rnd.next(8, 14);
    } else {
        r = rnd.next(6, 12);
        c = rnd.next(6, 12);
    }
    int t = rnd.next(1, 10);

    vector<string> board(r, string(c, '.'));
    vector<pair<int, int>> cells;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cells.emplace_back(i, j);
        }
    }
    shuffle(cells.begin(), cells.end());

    pair<int, int> start;
    if (mode == 2) {
        start = {rnd.next(r), rnd.next(0, min(c - 1, 2))};
    } else {
        start = cells.back();
        cells.pop_back();
    }
    board[start.first][start.second] = 'G';

    auto freeCells = [&]() {
        vector<pair<int, int>> result;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (board[i][j] == '.') {
                    result.emplace_back(i, j);
                }
            }
        }
        shuffle(result.begin(), result.end());
        return result;
    };

    int wallTarget;
    if (mode == 0) {
        wallTarget = 1;
    } else if (mode == 1) {
        wallTarget = rnd.next(max(1, r + c - 5), max(1, r + c));
    } else if (mode == 2) {
        wallTarget = rnd.next(1, max(1, r - 1));
    } else {
        wallTarget = rnd.next(1, max(1, r * c / 5));
    }

    if (mode == 1) {
        int wallCol = rnd.next(c);
        int gap1 = rnd.next(r);
        int gap2 = rnd.next(r);
        for (int i = 0; i < r; ++i) {
            if (i != gap1 && i != gap2 && board[i][wallCol] == '.') {
                board[i][wallCol] = '#';
            }
        }
    } else if (mode == 2) {
        int wallRow = rnd.next(r);
        for (int j = rnd.next(1, max(1, c / 2)); j < c; j += rnd.next(2, 4)) {
            if (board[wallRow][j] == '.') {
                board[wallRow][j] = '#';
            }
        }
    }

    vector<pair<int, int>> open = freeCells();
    for (int i = 0; i < wallTarget && !open.empty(); ++i) {
        auto [x, y] = open.back();
        open.pop_back();
        board[x][y] = '#';
    }

    vector<pair<int, int>> sweetCandidates;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (board[i][j] == '.') {
                int dist = abs(i - start.first) + abs(j - start.second);
                if (mode != 3 || dist <= t + rnd.next(0, 3)) {
                    sweetCandidates.emplace_back(i, j);
                }
            }
        }
    }
    if (sweetCandidates.empty()) {
        sweetCandidates = freeCells();
    }
    shuffle(sweetCandidates.begin(), sweetCandidates.end());

    int sweetTarget = rnd.next(1, max(1, min((int)sweetCandidates.size(), 8)));
    for (int i = 0; i < sweetTarget; ++i) {
        auto [x, y] = sweetCandidates[i];
        board[x][y] = 'S';
    }

    int wallCount = 0;
    int sweetCount = 0;
    for (const string& row : board) {
        wallCount += count(row.begin(), row.end(), '#');
        sweetCount += count(row.begin(), row.end(), 'S');
    }

    if (wallCount == 0 || sweetCount == 0) {
        vector<pair<int, int>> remaining = freeCells();
        if (wallCount == 0 && !remaining.empty()) {
            auto [x, y] = remaining.back();
            remaining.pop_back();
            board[x][y] = '#';
        }
        if (sweetCount == 0 && !remaining.empty()) {
            auto [x, y] = remaining.back();
            board[x][y] = 'S';
        }
    }

    println(r, c, t);
    for (const string& row : board) {
        println(row);
    }
}
