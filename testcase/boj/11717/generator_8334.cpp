#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for board size bias
    bool smallH = rnd.next(0, 1);
    int H = smallH ? rnd.wnext(20, -1) + 1 : rnd.wnext(20, 1) + 1;
    bool smallW = rnd.next(0, 1);
    int W = smallW ? rnd.wnext(20, -1) + 1 : rnd.wnext(20, 1) + 1;

    vector<string> board(H, string(W, '.'));

    // Choose pattern type for diversity
    int type = rnd.next(0, 4);
    if (type == 0) {
        // Random sparse or dense marks
        vector<double> ps = {0.1, 0.3, 0.5, 0.7, 0.9};
        double p = rnd.any(ps);
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (rnd.next() < p)
                    board[i][j] = 'X';
    } else if (type == 1) {
        // All empty (.) board
        // nothing to do
    } else if (type == 2) {
        // Almost all X except a few empties
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                board[i][j] = 'X';
        int total = H * W;
        int E = rnd.next(1, max(total / 4, 1));
        vector<int> idx(total);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        for (int k = 0; k < E; k++) {
            int v = idx[k];
            board[v / W][v % W] = '.';
        }
    } else if (type == 3) {
        // Striped pattern with flips
        bool horizontal = rnd.next(0, 1) == 0;
        int limit = horizontal ? H : W;
        int stripeLen = rnd.next(1, limit);
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                int idx = horizontal ? i : j;
                board[i][j] = ((idx / stripeLen) % 2 == 0 ? 'X' : '.');
            }
        }
        vector<double> flips = {0.05, 0.1, 0.2};
        double fp = rnd.any(flips);
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (rnd.next() < fp)
                    board[i][j] = (board[i][j] == 'X' ? '.' : 'X');
    } else {
        // Central cross with random extras
        int midR = H / 2, midC = W / 2;
        for (int i = 0; i < H; i++)
            board[i][midC] = 'X';
        for (int j = 0; j < W; j++)
            board[midR][j] = 'X';
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (board[i][j] == '.' && rnd.next() < 0.2)
                    board[i][j] = 'X';
    }

    // Ensure at least one empty cell
    int empties = 0;
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (board[i][j] == '.')
                empties++;
    if (empties == 0) {
        int r = rnd.next(0, H - 1);
        int c = rnd.next(0, W - 1);
        board[r][c] = '.';
    }

    // Output
    println(H, W);
    for (int i = 0; i < H; i++)
        println(board[i]);

    return 0;
}
