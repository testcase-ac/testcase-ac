#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose dimensions so that there is room for O, R, B
    int N, M;
    do {
        N = rnd.next(3, 10);
        M = rnd.next(3, 10);
    } while ((N - 2) * (M - 2) < 3);

    // Collect all interior cells
    vector<pair<int,int>> cells;
    for (int i = 1; i <= N - 2; i++) {
        for (int j = 1; j <= M - 2; j++) {
            cells.emplace_back(i, j);
        }
    }

    // Pick distinct positions for hole, red, blue
    shuffle(cells.begin(), cells.end());
    auto hole = cells[0];
    auto red  = cells[1];
    auto blue = cells[2];

    // Remaining cells for walls vs empty
    vector<pair<int,int>> rem(cells.begin() + 3, cells.end());
    int totRem = rem.size();
    // Hyper-parameter t for biasing wall count: -1 => few walls, 0 => uniform, 1 => many walls
    int t = rnd.any(vector<int>{-1, 0, 1});
    int wallsCount = rnd.wnext(totRem + 1, t); // in [0..totRem]
    shuffle(rem.begin(), rem.end());
    set<pair<int,int>> walls(rem.begin(), rem.begin() + wallsCount);

    // Build board
    vector<string> grid(N, string(M, '.'));
    // Outer walls
    for (int i = 0; i < N; i++) {
        grid[i][0] = grid[i][M-1] = '#';
    }
    for (int j = 0; j < M; j++) {
        grid[0][j] = grid[N-1][j] = '#';
    }
    // Place interior walls
    for (auto &p : walls) {
        grid[p.first][p.second] = '#';
    }
    // Place special cells
    grid[hole.first][hole.second] = 'O';
    grid[red.first][red.second]     = 'R';
    grid[blue.first][blue.second]   = 'B';

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i].c_str());
    }

    return 0;
}
