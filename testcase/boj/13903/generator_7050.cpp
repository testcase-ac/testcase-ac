#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter biases for dimensions
    int Rmax = 25, Cmax = 25;
    int tR = rnd.any(vector<int>{-1, 0, 1});
    int tC = rnd.any(vector<int>{-1, 0, 1});
    int R = rnd.wnext(Rmax, tR) + 1;
    int C = rnd.wnext(Cmax, tC) + 1;
    // Generate grid with varying density of '1's
    vector<double> densities = {0.1, 0.3, 0.5, 0.7, 0.9};
    double p1 = rnd.any(densities);
    vector<vector<int>> grid(R, vector<int>(C));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            grid[i][j] = (rnd.next() < p1 ? 1 : 0);
        }
    }
    // Sometimes ensure at least one start and end
    if (rnd.next() < 0.7) {
        bool has1 = false;
        for (int j = 0; j < C; j++) if (grid[0][j] == 1) has1 = true;
        if (!has1) grid[0][rnd.next(0, C-1)] = 1;
        has1 = false;
        for (int j = 0; j < C; j++) if (grid[R-1][j] == 1) has1 = true;
        if (!has1) grid[R-1][rnd.next(0, C-1)] = 1;
    }
    // Movement rules count with bias
    int maxMoves = (2*R+1)*(2*C+1) - 1;
    int tN = rnd.any(vector<int>{-1, 0, 1});
    int N = rnd.wnext(11, tN); // yields [0..10]
    N = min(N, maxMoves);
    // Build all possible moves except (0,0)
    vector<pair<int,int>> moves;
    for (int dr = -R; dr <= R; dr++) {
        for (int dc = -C; dc <= C; dc++) {
            if (dr == 0 && dc == 0) continue;
            moves.emplace_back(dr, dc);
        }
    }
    shuffle(moves.begin(), moves.end());
    // Output
    println(R, C);
    for (auto &row : grid) println(row);
    println(N);
    for (int i = 0; i < N; i++) {
        println(moves[i].first, moves[i].second);
    }
    return 0;
}
