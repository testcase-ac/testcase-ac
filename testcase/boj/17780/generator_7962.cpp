#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Board size and number of pieces
    int N = rnd.next(4, 12);
    int maxK = min(10, N * N);
    int K = rnd.next(4, maxK);

    // Hyper-parameters for color densities
    int tot = 100;
    int blueThresh = rnd.next(0, tot);
    int redThresh = rnd.next(0, tot - blueThresh);

    // Generate board colors: 0=white, 1=red, 2=blue
    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int r = rnd.next(0, tot - 1);
            if (r < blueThresh) board[i][j] = 2;
            else if (r < blueThresh + redThresh) board[i][j] = 1;
            else board[i][j] = 0;
        }
    }

    // Prepare lists of available border and interior cells for piece placement
    vector<pair<int,int>> border, interior;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == 1 || i == N || j == 1 || j == N) border.emplace_back(i, j);
            else interior.emplace_back(i, j);
        }
    }

    // Hyper-parameter: probability (in percent) to pick a border cell
    int p_border = rnd.next(0, 100);

    // Generate piece positions and directions
    vector<tuple<int,int,int>> pieces;
    for (int p = 0; p < K; p++) {
        pair<int,int> pos;
        // Decide border vs interior
        if (!border.empty() && rnd.next(0, 99) < p_border) {
            int idx = rnd.next(0, (int)border.size() - 1);
            pos = border[idx];
            border[idx] = border.back();
            border.pop_back();
        } else {
            if (!interior.empty()) {
                int idx = rnd.next(0, (int)interior.size() - 1);
                pos = interior[idx];
                interior[idx] = interior.back();
                interior.pop_back();
            } else {
                int idx = rnd.next(0, (int)border.size() - 1);
                pos = border[idx];
                border[idx] = border.back();
                border.pop_back();
            }
        }
        int dir = rnd.next(1, 4); // 1=→, 2=←, 3=↑, 4=↓
        pieces.emplace_back(pos.first, pos.second, dir);
    }

    // Output
    println(N, K);
    for (auto &row : board) println(row);
    for (auto &t : pieces) {
        int r, c, d;
        tie(r, c, d) = t;
        println(r, c, d);
    }
    return 0;
}
