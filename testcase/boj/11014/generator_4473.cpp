#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small but varied
    int C = rnd.next(1, 5);
    println(C);

    for (int tc = 0; tc < C; tc++) {
        // Classroom dimensions: small for hand-check
        int N = rnd.next(1, 10);
        int M = rnd.next(1, 10);

        // Initialize all seats as free ('.')
        vector<string> grid(N, string(M, '.'));

        // Hyper-parameter: full broken row/column clusters
        if (rnd.next() < 0.1) {
            int row = rnd.next(0, N - 1);
            for (int j = 0; j < M; j++) grid[row][j] = 'x';
        }
        if (rnd.next() < 0.1) {
            int col = rnd.next(0, M - 1);
            for (int i = 0; i < N; i++) grid[i][col] = 'x';
        }

        // Hyper-parameter: small broken clusters
        int numClusters = rnd.next(0, 3);
        for (int k = 0; k < numClusters; k++) {
            int ci = rnd.next(0, N - 1);
            int cj = rnd.next(0, M - 1);
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = ci + di, nj = cj + dj;
                    if (ni >= 0 && ni < N && nj >= 0 && nj < M) {
                        grid[ni][nj] = 'x';
                    }
                }
            }
        }

        // Hyper-parameter: random broken density up to 50%
        double pBroken = rnd.next() * 0.5;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == '.' && rnd.next() < pBroken) {
                    grid[i][j] = 'x';
                }
            }
        }

        // Output this test case
        println(N, M);
        for (int i = 0; i < N; i++) {
            printf("%s\n", grid[i].c_str());
        }
    }

    return 0;
}
