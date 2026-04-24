#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for dimensions
    int M, N;
    double d = rnd.next();
    if (d < 0.1) {
        // single row
        M = 1;
        N = rnd.next(1, 12);
    } else if (d < 0.2) {
        // single column
        N = 1;
        M = rnd.next(1, 12);
    } else {
        // block sizes: small, medium, large
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            M = rnd.next(2, 5);
            N = rnd.next(2, 5);
        } else if (mode == 1) {
            M = rnd.next(6, 9);
            N = rnd.next(6, 9);
        } else {
            M = rnd.next(10, 12);
            N = rnd.next(10, 12);
        }
    }

    // Hyper-parameter for press density
    vector<double> ps = {0.2, 0.5, 0.8};
    double p = rnd.any(ps);

    // Generate a random solution X (press matrix)
    vector<vector<int>> X(M, vector<int>(N, 0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            X[i][j] = (rnd.next() < p) ? 1 : 0;
        }
    }

    // Simulate on an all-zero grid to get the initial state S
    vector<vector<int>> S(M, vector<int>(N, 0));
    int dx[5] = {0, 0, 0, 1, -1};
    int dy[5] = {0, 1, -1, 0, 0};
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (X[i][j] == 1) {
                for (int k = 0; k < 5; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if (ni >= 0 && ni < M && nj >= 0 && nj < N) {
                        S[ni][nj] ^= 1;
                    }
                }
            }
        }
    }

    // Output the test case
    println(M, N);
    for (int i = 0; i < M; i++) {
        println(S[i]);
    }
    return 0;
}
