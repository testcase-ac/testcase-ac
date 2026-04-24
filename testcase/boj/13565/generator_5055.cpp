#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int M = rnd.next(2, 10);
    int N = rnd.next(2, 10);
    double zeroProb = rnd.next(0.3, 0.7);  // probability of a white (0) cell

    // Initialize grid with random cells
    vector<string> grid(M, string(N, '1'));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (rnd.next() < zeroProb)
                grid[i][j] = '0';
        }
    }

    // Mode: force a YES case or a NO case
    int mode = rnd.next(0, 1);
    if (mode == 1) {
        // YES case: carve a path of zeros from top row to bottom row
        int col = rnd.next(0, N - 1);
        for (int i = 0; i < M; i++) {
            grid[i][col] = '0';
            // Randomly step left or right
            if (N > 1 && rnd.next() < 0.5) {
                int d = rnd.next(0, 1) ? 1 : -1;
                if (col + d >= 0 && col + d < N) {
                    col += d;
                    grid[i][col] = '0';
                }
            }
        }
    } else {
        // NO case: place a full black barrier row (except trivial M=2)
        if (M > 2) {
            int block = rnd.next(1, M - 2);
            for (int j = 0; j < N; j++)
                grid[block][j] = '1';
        } else {
            // M == 2, block either top or bottom fully
            int block = rnd.next(0, 1);
            for (int j = 0; j < N; j++)
                grid[block][j] = '1';
        }
    }

    // Output
    println(M, N);
    for (int i = 0; i < M; i++)
        println(grid[i]);

    return 0;
}
