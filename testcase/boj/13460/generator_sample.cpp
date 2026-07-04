#include "testlib.h"

#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n, m;
    do {
        n = rnd.next(3, 10);
        m = rnd.next(3, 10);
    } while ((n - 2) * (m - 2) < 3);

    vector<string> board(n, string(m, '.'));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
                board[r][c] = '#';
            }
        }
    }

    vector<pair<int, int>> cells;
    for (int r = 1; r + 1 < n; ++r) {
        for (int c = 1; c + 1 < m; ++c) {
            cells.push_back({r, c});
        }
    }

    int mode = rnd.next(0, 3);
    if (mode == 0) {
        double wallProb = rnd.next(0.0, 0.55);
        for (auto [r, c] : cells) {
            if (rnd.next() < wallProb) {
                board[r][c] = '#';
            }
        }
    } else if (mode == 1) {
        int stride = rnd.next(2, 4);
        bool vertical = rnd.next(0, 1);
        for (auto [r, c] : cells) {
            bool wall = vertical ? (c % stride == 0) : (r % stride == 0);
            if (wall && rnd.next() < 0.75) {
                board[r][c] = '#';
            }
        }
    } else {
        int wallCount = rnd.next(0, (int)cells.size() / 2);
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < wallCount; ++i) {
            board[cells[i].first][cells[i].second] = '#';
        }
    }

    shuffle(cells.begin(), cells.end());
    board[cells[0].first][cells[0].second] = 'O';
    board[cells[1].first][cells[1].second] = 'R';
    board[cells[2].first][cells[2].second] = 'B';

    println(n, m);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
