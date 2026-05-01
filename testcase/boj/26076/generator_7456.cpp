#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N, M;
    // Choose orientation: 0 = single row, 1 = single column, 2 = 2D grid
    int orient = rnd.next(0, 2);
    if (orient == 0) {
        N = 1;
        M = rnd.next(3, 15);
    } else if (orient == 1) {
        N = rnd.next(3, 15);
        M = 1;
    } else {
        N = rnd.next(2, 10);
        M = rnd.next(2, 10);
    }
    vector<vector<int>> grid(N, vector<int>(M, 1));
    // Scenario: 0 = random obstacles, 1 = unique winding path, 2 = two disjoint corridors
    int scen = rnd.next(0, 2);
    if (scen == 2 && orient != 2) {
        // fallback if not 2D
        scen = rnd.next(0, 1);
    }
    if (scen == 0) {
        // random obstacles
        double p = rnd.next(0, 6) / 10.0; // obstacle probability in [0,0.6]
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if ((i == 0 && j == 0) || (i == N-1 && j == M-1)) {
                    grid[i][j] = 0;
                } else {
                    grid[i][j] = (rnd.next() < p ? 1 : 0);
                }
            }
        }
    } else if (scen == 1) {
        // unique winding path: carve a random permutation of rights and downs
        // others remain obstacles
        vector<char> moves;
        for (int k = 0; k < M-1; k++) moves.push_back('R');
        for (int k = 0; k < N-1; k++) moves.push_back('D');
        shuffle(moves.begin(), moves.end());
        int x = 0, y = 0;
        grid[0][0] = 0;
        for (char c : moves) {
            if (c == 'R') y++;
            else x++;
            grid[x][y] = 0;
        }
    } else {
        // scen == 2, two disjoint corridors in 2D
        // fill grid with obstacles except two corridors
        // path1: down along col0 then right along row N-1
        for (int i = 0; i < N; i++) grid[i][0] = 0;
        for (int j = 0; j < M; j++) grid[N-1][j] = 0;
        // path2: right along row0 then down along col M-1
        for (int j = 0; j < M; j++) grid[0][j] = 0;
        for (int i = 0; i < N; i++) grid[i][M-1] = 0;
        // start and end already covered
    }
    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }
    return 0;
}
