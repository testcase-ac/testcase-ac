#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: grid size
    int N = rnd.next(4, 10);

    // Hyper-parameter: obstacle density
    vector<double> densities = {0.0, 0.2, 0.5, 0.7};
    double p = rnd.any(densities);

    // Random orientations: 0 = horizontal, 1 = vertical
    int dirB = rnd.next(0, 1);
    int dirE = rnd.next(0, 1);

    // Initialize empty grid
    vector<string> grid(N, string(N, '0'));

    // Function to pick a valid center position for a log of length 3
    auto pickPos = [&](int dir) {
        if (dir == 0) { // horizontal: row [0,N-1], center col [1,N-2]
            int r = rnd.next(0, N - 1);
            int c = rnd.next(1, N - 2);
            return make_pair(r, c);
        } else { // vertical: center row [1,N-2], col [0,N-1]
            int r = rnd.next(1, N - 2);
            int c = rnd.next(0, N - 1);
            return make_pair(r, c);
        }
    };

    // Place the initial log 'B'
    auto posB = pickPos(dirB);
    int rB = posB.first, cB = posB.second;
    if (dirB == 0) { // horizontal
        grid[rB][cB-1] = 'B';
        grid[rB][cB]   = 'B';
        grid[rB][cB+1] = 'B';
    } else { // vertical
        grid[rB-1][cB] = 'B';
        grid[rB][cB]   = 'B';
        grid[rB+1][cB] = 'B';
    }

    // Place the target 'E' ensuring no overlap with 'B'
    int rE, cE;
    while (true) {
        auto posE = pickPos(dirE);
        rE = posE.first; cE = posE.second;
        bool ok = true;
        if (dirE == 0) {
            for (int dc = -1; dc <= 1; dc++)
                if (grid[rE][cE+dc] != '0') ok = false;
        } else {
            for (int dr = -1; dr <= 1; dr++)
                if (grid[rE+dr][cE] != '0') ok = false;
        }
        if (ok) break;
    }
    if (dirE == 0) {
        grid[rE][cE-1] = 'E';
        grid[rE][cE]   = 'E';
        grid[rE][cE+1] = 'E';
    } else {
        grid[rE-1][cE] = 'E';
        grid[rE][cE]   = 'E';
        grid[rE+1][cE] = 'E';
    }

    // Fill obstacles ('1') with probability p
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == '0' && rnd.next() < p) {
                grid[i][j] = '1';
            }
        }
    }

    // Output the grid
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
