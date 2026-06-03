#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<int>> board(5, vector<int>(5, 0));
    vector<pair<int, int>> cells;
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());

    int mode = rnd.next(0, 5);
    double wallProb = 0.0;
    double sevenProb = 0.0;

    if (mode == 0) {
        wallProb = rnd.next(0.0, 0.12);
        sevenProb = rnd.next(0.0, 0.16);
    } else if (mode == 1) {
        wallProb = rnd.next(0.16, 0.34);
        sevenProb = rnd.next(0.0, 0.20);
    } else if (mode == 2) {
        wallProb = rnd.next(0.0, 0.14);
        sevenProb = rnd.next(0.28, 0.58);
    } else if (mode == 3) {
        wallProb = rnd.next(0.28, 0.48);
        sevenProb = rnd.next(0.20, 0.45);
    } else {
        wallProb = rnd.next(0.08, 0.24);
        sevenProb = rnd.next(0.08, 0.28);
    }

    for (auto [r, c] : cells) {
        double x = rnd.next();
        if (x < wallProb) {
            board[r][c] = -1;
        } else if (x < wallProb + sevenProb) {
            board[r][c] = 7;
        }
    }

    pair<int, int> start = cells[0];
    pair<int, int> target = cells[1];
    board[start.first][start.second] = 0;
    board[target.first][target.second] = 1;

    if (mode == 4) {
        for (int d = 0; d < 4; ++d) {
            int dr[4] = {-1, 1, 0, 0};
            int dc[4] = {0, 0, -1, 1};
            int nr = target.first + dr[d];
            int nc = target.second + dc[d];
            if (0 <= nr && nr < 5 && 0 <= nc && nc < 5 &&
                make_pair(nr, nc) != start) {
                board[nr][nc] = -1;
            }
        }
        board[target.first][target.second] = 1;
    }

    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            if (c) {
                cout << ' ';
            }
            cout << board[r][c];
        }
        cout << '\n';
    }
    println(start.first, start.second);

    return 0;
}
