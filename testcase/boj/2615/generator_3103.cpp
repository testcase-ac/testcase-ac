#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

static bool hasFiveOrMore(const vector<vector<int>>& b) {
    int n = 19;
    int dx[4] = {0, 1, 1, -1};
    int dy[4] = {1, 0, 1, 1};
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int col = b[i][j];
            if (col == 0) continue;
            for (int d = 0; d < 4; d++) {
                int pi = i - dx[d], pj = j - dy[d];
                if (pi >= 1 && pi <= n && pj >= 1 && pj <= n && b[pi][pj] == col)
                    continue; // not start of sequence
                int cnt = 0;
                int x = i, y = j;
                while (x >= 1 && x <= n && y >= 1 && y <= n && b[x][y] == col) {
                    cnt++;
                    x += dx[d];
                    y += dy[d];
                }
                if (cnt >= 5) return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int N = 19;

    // Decide whether to include a win (about 20% chance)
    bool wantWin = (rnd.next(0, 4) == 0);

    // Prepare empty board with 1-based indexing
    vector<vector<int>> board(N+1, vector<int>(N+1, 0));

    // If we will place a winning sequence, choose its params now
    int winColor = 0, sr = 0, sc = 0, dr = 0, dc = 0;
    vector<pair<int,int>> reserved;
    if (wantWin) {
        winColor = rnd.any(vector<int>{1, 2});
        int dir = rnd.next(0, 3);
        // directions: 0=horiz,1=vert,2=diag-down,3=diag-up
        int dx[4] = {0, 1, 1, -1};
        int dy[4] = {1, 0, 1, 1};
        dr = dx[dir];
        dc = dy[dir];
        // choose start so that 5 fit in board
        int rlo = 1, rhi = N, clo = 1, chi = N;
        if (dr == 0) { // horizontal
            chi = N - 4;
        } else if (dc == 0) { // vertical
            rhi = N - 4;
        } else if (dr == 1 && dc == 1) { // diag-down
            rhi = N - 4;
            chi = N - 4;
        } else if (dr == -1 && dc == 1) { // diag-up
            rlo = 5;
            chi = N - 4;
        }
        sr = rnd.next(rlo, rhi);
        sc = rnd.next(clo, chi);
        for (int i = 0; i < 5; i++) {
            int r = sr + i*dr, c = sc + i*dc;
            reserved.emplace_back(r, c);
        }
    }

    // Build list of all cells and shuffle
    vector<pair<int,int>> cells;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());

    // Decide how many filler stones to attempt
    int maxFill = rnd.wnext(31, -1); // bias toward fewer stones
    int filled = 0, idx = 0;
    while (filled < maxFill && idx < (int)cells.size()) {
        int r = cells[idx].first, c = cells[idx].second;
        idx++;
        // don't fill reserved cells if we're going to place a win
        bool isReserved = false;
        for (auto &p : reserved) {
            if (p.first == r && p.second == c) {
                isReserved = true;
                break;
            }
        }
        if (isReserved) continue;
        int col = rnd.any(vector<int>{1,2});
        board[r][c] = col;
        if (hasFiveOrMore(board)) {
            board[r][c] = 0; // undo if it creates any five-or-more
        } else {
            filled++;
        }
    }

    // Now place the winning sequence (if any)
    if (wantWin) {
        for (auto &p : reserved) {
            board[p.first][p.second] = winColor;
        }
    }

    // Output the board
    for (int i = 1; i <= N; i++) {
        vector<int> row;
        for (int j = 1; j <= N; j++)
            row.push_back(board[i][j]);
        println(row);
    }
    return 0;
}
