#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small grid sizes
    int N = rnd.next(2, 10);
    int M = rnd.next(2, 10);
    int D = rnd.next(1, min(N, M));

    // Hyper-parameter: obstacle density percent biased
    int bias = rnd.next(-2, 2);
    int p = rnd.wnext(101, bias); // 0..100 percent

    // Initialize grid
    vector<string> grid(N, string(M, '.'));

    // Choose pattern for diversity
    int pattern = rnd.next(0, 2);
    // 0: uniform randomness
    // 1: horizontal barrier with holes
    // 2: cluster block
    if (pattern == 0) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                grid[i][j] = (rnd.next(100) < p ? '#' : '.');
            }
        }
    } else if (pattern == 1) {
        // fill uniformly
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                grid[i][j] = (rnd.next(100) < p ? '#' : '.');
            }
        }
        // horizontal barrier
        int barrier = rnd.next(0, N-1);
        for (int j = 0; j < M; j++) {
            grid[barrier][j] = '#';
        }
        int holes = rnd.next(1, M);
        for (int t = 0; t < holes; t++) {
            int c = rnd.next(0, M-1);
            grid[barrier][c] = '.';
        }
    } else {
        // fill uniformly
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                grid[i][j] = (rnd.next(100) < p ? '#' : '.');
            }
        }
        // block cluster
        int h = rnd.next(1, max(1, N/2));
        int w = rnd.next(1, max(1, M/2));
        int top = rnd.next(0, N - h);
        int left = rnd.next(0, M - w);
        for (int i = top; i < top + h; i++) {
            for (int j = left; j < left + w; j++) {
                grid[i][j] = '#';
            }
        }
    }

    // Ensure start and end are clear
    grid[0][0] = '.';
    grid[N-1][M-1] = '.';

    // Output
    println(N, M, D);
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
