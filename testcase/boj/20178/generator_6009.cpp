#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// Check if binary matrix A (NxN) is invertible over GF(2)
bool isInvertible(const vector<vector<int>>& A) {
    int n = A.size();
    vector<vector<int>> B = A;
    int row = 0;
    for (int col = 0; col < n && row < n; ++col) {
        int sel = -1;
        for (int i = row; i < n; ++i) {
            if (B[i][col]) { sel = i; break; }
        }
        if (sel < 0) continue;
        swap(B[sel], B[row]);
        for (int i = 0; i < n; ++i) {
            if (i != row && B[i][col]) {
                for (int j = col; j < n; ++j)
                    B[i][j] ^= B[row][j];
            }
        }
        row++;
    }
    return row == n;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size of the system: between 3 and 10 for readability
    int N = rnd.next(3, 10);

    // Decide whether to generate an invertible (solvable) or singular (unsolvable) matrix
    bool wantInvert = (rnd.next(0, 9) < 7); // ~70% invertible, ~30% singular

    vector<vector<int>> A;
    // Try until we get a matrix matching our invertibility requirement
    while (1) {
        // Hyper-parameter: choose density of ones
        double density;
        if (wantInvert) {
            // for invertible, try low or high density to vary patterns
            if (rnd.next(0,1) == 0) density = rnd.next(0.1, 0.5);
            else                    density = rnd.next(0.5, 0.9);
        } else {
            // for singular, allow full range
            density = rnd.next(0.1, 0.9);
        }

        // Fill with random bits
        A.assign(N, vector<int>(N,0));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                A[i][j] = (rnd.next() < density) ? 1 : 0;
            }
        }
        // Ensure no row is all-zero
        for (int i = 0; i < N; ++i) {
            bool any = false;
            for (int j = 0; j < N; ++j) if (A[i][j]) { any = true; break; }
            if (!any) {
                int j = rnd.next(0, N-1);
                A[i][j] = 1;
            }
        }
        // Ensure no column is all-zero
        for (int j = 0; j < N; ++j) {
            bool any = false;
            for (int i = 0; i < N; ++i) if (A[i][j]) { any = true; break; }
            if (!any) {
                int i = rnd.next(0, N-1);
                A[i][j] = 1;
            }
        }
        // Check invertibility
        if (isInvertible(A) == wantInvert) break;
    }

    // Shuffle rows and columns for variety
    vector<int> rperm(N), cperm(N);
    iota(rperm.begin(), rperm.end(), 0);
    iota(cperm.begin(), cperm.end(), 0);
    if (rnd.next(0,1)) shuffle(rperm.begin(), rperm.end());
    if (rnd.next(0,1)) shuffle(cperm.begin(), cperm.end());

    // Output
    println(N);
    for (int i = 0; i < N; ++i) {
        vector<int> row(N);
        for (int j = 0; j < N; ++j) {
            row[j] = A[rperm[i]][cperm[j]];
        }
        println(row);
    }
    return 0;
}
