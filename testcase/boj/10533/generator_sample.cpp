#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 4);
    int mode = rnd.next(0, 3);
    int w = 1;
    int h = 1;

    do {
        if (mode == 0) {
            w = rnd.next(2, 6);
            h = rnd.next(2, 6);
        } else if (mode == 1) {
            w = rnd.next(5, 10);
            h = rnd.next(1, 3);
        } else if (mode == 2) {
            w = rnd.next(1, 3);
            h = rnd.next(5, 10);
        } else {
            w = rnd.next(6, 10);
            h = rnd.next(6, 10);
        }
    } while (w * h < n + 1);

    int limit = rnd.next(1, 10);
    vector<string> board(h, string(w, '.'));
    vector<pair<int, int>> cells;
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());

    board[cells[0].first][cells[0].second] = 'X';
    for (int robot = 1; robot <= n; ++robot) {
        board[cells[robot].first][cells[robot].second] = char('0' + robot);
    }

    double wall_probability = 0.0;
    if (mode == 0) {
        wall_probability = rnd.next(0.0, 0.28);
    } else if (mode == 1 || mode == 2) {
        wall_probability = rnd.next(0.0, 0.18);
    } else {
        wall_probability = rnd.next(0.12, 0.38);
    }

    for (int index = n + 1; index < static_cast<int>(cells.size()); ++index) {
        int r = cells[index].first;
        int c = cells[index].second;
        if (rnd.next() < wall_probability) {
            board[r][c] = 'W';
        }
    }

    if (mode == 3 && h >= 4 && w >= 4) {
        if (rnd.next(0, 1) == 0) {
            int row = rnd.next(1, h - 2);
            for (int c = 0; c < w; ++c) {
                if (board[row][c] == '.' && rnd.next(0, 3) != 0) {
                    board[row][c] = 'W';
                }
            }
        } else {
            int col = rnd.next(1, w - 2);
            for (int r = 0; r < h; ++r) {
                if (board[r][col] == '.' && rnd.next(0, 3) != 0) {
                    board[r][col] = 'W';
                }
            }
        }
    }

    println(n, w, h, limit);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
