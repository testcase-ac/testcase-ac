#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: small grid size
    int M = rnd.next(1, 5);
    int N = rnd.next(1, 5);

    // Hyper-parameter: weights for each blind type 0..4
    vector<int> w(5);
    int total_w = 0;
    for (int i = 0; i < 5; i++) {
        w[i] = rnd.next(0, 10);
        total_w += w[i];
    }
    // ensure non-empty pool
    if (total_w == 0) {
        for (int i = 0; i < 5; i++) {
            w[i] = 1;
        }
        total_w = 5;
    }
    // build sampling pool
    vector<int> pool;
    for (int i = 0; i < 5; i++) {
        for (int t = 0; t < w[i]; t++) {
            pool.push_back(i);
        }
    }

    // assign a type to each window
    vector<vector<int>> typ(M, vector<int>(N));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            typ[i][j] = rnd.any(pool);
        }
    }

    // prepare the ASCII grid
    int rows = 5 * M + 1;
    int cols = 5 * N + 1;
    vector<string> grid(rows, string(cols, ' '));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // horizontal separators
            if (i % 5 == 0) {
                grid[i][j] = '#';
            } else if (j % 5 == 0) {
                grid[i][j] = '#';
            } else {
                grid[i][j] = '.'; // placeholder
            }
        }
    }

    // fill each window
    for (int fi = 0; fi < M; fi++) {
        for (int fj = 0; fj < N; fj++) {
            int t = typ[fi][fj];
            // block top-left corner of window at (fi*5+1, fj*5+1)
            int base_i = fi * 5 + 1;
            int base_j = fj * 5 + 1;
            for (int di = 0; di < 4; di++) {
                for (int dj = 0; dj < 4; dj++) {
                    // star if in the top t rows
                    if (di < t) grid[base_i + di][base_j + dj] = '*';
                    else grid[base_i + di][base_j + dj] = '.';
                }
            }
        }
    }

    // output
    println(M, N);
    for (int i = 0; i < rows; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
