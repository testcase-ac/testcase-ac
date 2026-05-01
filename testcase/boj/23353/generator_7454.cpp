#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a small to medium board size
    int N = rnd.next(2, 12);
    vector<vector<int>> board(N, vector<int>(N, 0));
    // Three modes: pure random, near-complete row with one white gap, near-complete diag with one white gap
    int mode = rnd.next(0, 2);
    if (N >= 3 && mode != 0) {
        // Length of the line to create (at least 2 to allow improvement)
        int L = rnd.next(2, N);
        // Position of the white gap in the line
        int gap = rnd.next(0, L - 1);
        if (mode == 1) {
            // Fill a row
            int row = rnd.next(0, N - 1);
            for (int j = 0; j < L; ++j) {
                board[row][j] = (j == gap ? 2 : 1);
            }
        } else {
            // Fill main down-right diagonal
            for (int k = 0; k < L; ++k) {
                board[k][k] = (k == gap ? 2 : 1);
            }
        }
        // Fill the rest of the board with low-density random stones
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == 0) {
                    int r = rnd.next(1, 100);
                    if (r <= 15) board[i][j] = 1;
                    else if (r <= 30) board[i][j] = 2;
                    else board[i][j] = 0;
                }
            }
        }
    } else {
        // Pure random distribution ensuring at least one black and one white
        int total = N * N;
        int W = rnd.next(1, total - 1);
        int B = rnd.next(1, total - W);
        int E = total - W - B;
        vector<int> cells;
        cells.reserve(total);
        for (int i = 0; i < W; ++i) cells.push_back(2);
        for (int i = 0; i < B; ++i) cells.push_back(1);
        for (int i = 0; i < E; ++i) cells.push_back(0);
        shuffle(cells.begin(), cells.end());
        int idx = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                board[i][j] = cells[idx++];
            }
        }
    }
    // Output
    println(N);
    for (auto &row : board) {
        println(row);
    }
    return 0;
}
