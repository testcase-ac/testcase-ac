#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size hyper-parameter
    int R = rnd.next(1, 10);
    int C = rnd.next(1, 10);
    int T = R * C;

    // Prepare all cells
    vector<pair<int,int>> cells;
    cells.reserve(T);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());

    // Walls: use weighted next to get varied density
    int Wmax = T / 3;
    int w_t = rnd.next(-1, 1);
    int W = rnd.wnext(Wmax + 1, w_t); // in [0..Wmax]

    int rem = T - W;
    // Cars and parking slots: random but ensure sum <= rem
    int maxCP = min(rem, 5);
    int Nc, Np;
    do {
        Nc = rnd.next(0, maxCP);
        Np = rnd.next(0, maxCP);
    } while (Nc + Np > rem);

    // Build grid
    vector<string> grid(R, string(C, '.'));
    int idx = 0;
    // Place walls
    for (int i = 0; i < W; i++) {
        auto [x, y] = cells[idx++];
        grid[x][y] = 'X';
    }
    // Place cars
    for (int i = 0; i < Nc; i++) {
        auto [x, y] = cells[idx++];
        grid[x][y] = 'C';
    }
    // Place parks
    for (int i = 0; i < Np; i++) {
        auto [x, y] = cells[idx++];
        grid[x][y] = 'P';
    }
    // Remaining are '.'

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        printf("%s\n", grid[i].c_str());
    }

    return 0;
}
