#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid dimensions
    int N = rnd.next(3, 10);
    int M = rnd.next(3, 10);
    int maxD = min(10, N + M);
    int D = rnd.next(1, maxD);

    // Prepare empty grid
    vector<vector<int>> grid(N, vector<int>(M, 0));

    // Choose distribution type: 0 = uniform, 1 = gradient, 2 = clusters
    int distType = rnd.next(0, 2);

    if (distType == 0) {
        // Uniform random density
        double density = rnd.next(10, 50) * 0.01;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (rnd.next() < density) grid[i][j] = 1;
            }
        }
    } else if (distType == 1) {
        // Row-wise gradient density: high at top, lower at bottom
        double baseDensity = rnd.next(20, 60) * 0.01;
        int maxLast = int(baseDensity * 100);
        double lastDensity = rnd.next(0, maxLast) * 0.01;
        for (int i = 0; i < N; i++) {
            double ratio = (N == 1 ? 0 : double(i) / (N - 1));
            double d = baseDensity + (lastDensity - baseDensity) * ratio;
            for (int j = 0; j < M; j++) {
                if (rnd.next() < d) grid[i][j] = 1;
            }
        }
    } else {
        // Clustered enemies
        int clusters = rnd.next(1, 3);
        for (int c = 0; c < clusters; c++) {
            int ci = rnd.next(0, N - 1);
            int cj = rnd.next(0, M - 1);
            int sz = rnd.next(1, min(5, N * M));
            for (int k = 0; k < sz; k++) {
                int di = rnd.next(-1, 1);
                int dj = rnd.next(-1, 1);
                int ni = max(0, min(N - 1, ci + di));
                int nj = max(0, min(M - 1, cj + dj));
                grid[ni][nj] = 1;
            }
        }
        // Fill some others lightly
        double extraDensity = rnd.next(5, 20) * 0.01;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == 0 && rnd.next() < extraDensity)
                    grid[i][j] = 1;
            }
        }
    }

    // Output
    println(N, M, D);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }

    return 0;
}
