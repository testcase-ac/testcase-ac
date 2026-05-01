#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
 Generator for "인구 이동"
 Produces one small but varied test case:
  - N in [2,7]
  - 1 ≤ L ≤ R ≤ 100
  - A[r][c] in [0,100]
  - Adds some outliers or uniform patches based on a hyperparameter
*/

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size
    int N = rnd.next(2, 7);

    // Choose L and R
    int L = rnd.next(1, 50);
    int R = rnd.next(L, 100);

    // Hyperparameter: probability of creating an "outlier" cell
    double outlier_prob = rnd.next(0.0, 0.3);

    // Hyperparameter: probability of uniform blocks
    double block_prob = rnd.next(0.0, 0.5);

    // Prepare grid
    vector<vector<int>> A(N, vector<int>(N));

    // Optionally fill one random block with similar values
    if (rnd.next() < block_prob) {
        // block size 2×2 or 3×3 if fits
        int bs = min(N, rnd.next(2, 3));
        int br = rnd.next(0, N - bs);
        int bc = rnd.next(0, N - bs);
        int base = rnd.next(0, 100);
        for (int i = 0; i < bs; i++) {
            for (int j = 0; j < bs; j++) {
                A[br + i][bc + j] = base + rnd.next(-5, 5);
                A[br + i][bc + j] = max(0, min(100, A[br + i][bc + j]));
            }
        }
    }

    // Fill the rest
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] == 0 && rnd.next() < outlier_prob) {
                // Make an outlier
                A[i][j] = rnd.next() < 0.5 ? 0 : 100;
            } else if (A[i][j] == 0) {
                // Normal random
                A[i][j] = rnd.next(0, 100);
            }
        }
    }

    // Output
    println(N, L, R);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << (j + 1 < N ? ' ' : '\n');
        }
    }
    return 0;
}
