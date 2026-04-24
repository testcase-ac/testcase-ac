#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

// Check for any winners: three identical non-dot chars in a row, col, or diag
set<char> find_winners(const vector<string>& b) {
    int N = b.size();
    set<char> w;
    // rows
    for (int i = 0; i < N; i++) {
        for (int j = 0; j + 2 < N; j++) {
            char c = b[i][j];
            if (c != '.' && b[i][j+1] == c && b[i][j+2] == c)
                w.insert(c);
        }
    }
    // cols
    for (int j = 0; j < N; j++) {
        for (int i = 0; i + 2 < N; i++) {
            char c = b[i][j];
            if (c != '.' && b[i+1][j] == c && b[i+2][j] == c)
                w.insert(c);
        }
    }
    // diag down-right
    for (int i = 0; i + 2 < N; i++) {
        for (int j = 0; j + 2 < N; j++) {
            char c = b[i][j];
            if (c != '.' && b[i+1][j+1] == c && b[i+2][j+2] == c)
                w.insert(c);
        }
    }
    // diag up-right
    for (int i = 2; i < N; i++) {
        for (int j = 0; j + 2 < N; j++) {
            char c = b[i][j];
            if (c != '.' && b[i-1][j+1] == c && b[i-2][j+2] == c)
                w.insert(c);
        }
    }
    return w;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide mode: 0 = no win, 1 = enforce one win
    int mode = rnd.next(0, 1);

    // Choose board size
    int N = (mode == 1 ? rnd.next(3, 10) : rnd.next(1, 10));

    // Alphabet uppercase
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    vector<string> board;
    char winner = 0;

    // Repeat until valid board generated
    while (true) {
        board.assign(N, string(N, '.'));
        double pEmpty = rnd.next(0.0, 1.0);

        // Prepare letter pools
        vector<char> pool;
        if (mode == 1) {
            // pick a winner letter
            winner = rnd.any(alpha);
            pool.push_back(winner);
            // some filler letters
            int k = rnd.next(1, 3);
            shuffle(alpha.begin(), alpha.end());
            for (char c : alpha) {
                if ((int)pool.size() >= 1 + k) break;
                if (c != winner) pool.push_back(c);
            }
        } else {
            // no-win mode: pick some letters
            int k = rnd.next(1, 5);
            shuffle(alpha.begin(), alpha.end());
            for (int i = 0; i < k; i++)
                pool.push_back(alpha[i]);
        }

        // Optionally decide a winning line if mode==1
        int win_t = rnd.next(0, 3);
        int wi = rnd.next(0, N-1), wj = rnd.next(0, N-1);
        // Fill randomly
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                bool onWin = false;
                if (mode == 1) {
                    // check if this (i,j) is part of chosen win line
                    if (win_t == 0 && i == wi && j >= wj && j < wj+3 && wj+2 < N) onWin = true;
                    if (win_t == 1 && j == wj && i >= wi && i < wi+3 && wi+2 < N) onWin = true;
                    if (win_t == 2 && i-wi == j-wj && i >= wi && j >= wj && i < wi+3 && wi+2 < N && wj+2 < N) onWin = true;
                    if (win_t == 3 && wi-i == j-wj && i <= wi && j >= wj && i >= wi-2 && wi < N && wj+2 < N) onWin = true;
                }
                if (onWin) {
                    board[i][j] = winner;
                } else {
                    if (rnd.next() < pEmpty) {
                        board[i][j] = '.';
                    } else {
                        board[i][j] = rnd.any(pool);
                    }
                }
            }
        }

        // Validate winners
        auto wset = find_winners(board);
        if (mode == 1) {
            if (wset.size() == 1 && *wset.begin() == winner)
                break;
        } else {
            if (wset.empty())
                break;
        }
    }

    // Output
    println(N);
    for (auto& row : board)
        println(row);

    return 0;
}
