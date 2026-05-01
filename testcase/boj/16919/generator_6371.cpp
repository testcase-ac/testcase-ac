#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size hyper-parameter: include edge cases 1..12
    int R = rnd.next(1, 12);
    int C = rnd.next(1, 12);

    // Initial bomb density hyper-parameter: cover empty, sparse, medium, full
    vector<double> dens = {0.0, 0.3, 0.6, 1.0};
    double p = rnd.any(dens);

    // Generate initial grid
    vector<string> grid(R, string(C, '.'));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (rnd.next() < p) {
                grid[i][j] = 'O';
            }
        }
    }

    // Time N hyper-parameter: capture all behavior cases of the bomberman pattern
    // 0 -> N = 1 (initial)
    // 1 -> N even (all bombs)
    // 2 -> N % 4 == 3
    // 3 -> N % 4 == 1 and N > 1
    int h = rnd.next(0, 3);
    long long N;
    if (h == 0) {
        N = 1;
    } else if (h == 1) {
        // Even N between 2 and 20
        N = rnd.next(1, 10) * 2LL;
    } else if (h == 2) {
        vector<int> mod3 = {3, 7, 11, 15, 19};
        N = rnd.any(mod3);
    } else {
        vector<int> mod1 = {5, 9, 13, 17};
        N = rnd.any(mod1);
    }

    // Output
    println(R, C, N);
    for (int i = 0; i < R; i++) {
        println(grid[i]);
    }

    return 0;
}
