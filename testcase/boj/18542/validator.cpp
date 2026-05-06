#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

// Multiply two n x n matrices modulo MOD
vector<vector<long long>> matMul(const vector<vector<long long>>& A,
                                 const vector<vector<long long>>& B) {
    int n = (int)A.size();
    vector<vector<long long>> C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            long long v = A[i][k];
            if (v == 0) continue;
            for (int j = 0; j < n; ++j) {
                C[i][j] = (C[i][j] + v * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// Compute determinant of n x n matrix modulo MOD using Gaussian elimination
long long detMod(vector<vector<long long>> A) {
    int n = (int)A.size();
    long long det = 1;
    int sign = 1;
    for (int col = 0; col < n; ++col) {
        int pivot = -1;
        for (int row = col; row < n; ++row) {
            if (A[row][col] != 0) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) {
            return 0;
        }
        if (pivot != col) {
            swap(A[pivot], A[col]);
            sign = -sign;
        }
        long long inv = 0;
        {
            // Fermat inverse because MOD is prime
            long long base = A[col][col];
            long long exp = MOD - 2;
            long long res = 1;
            base %= MOD;
            if (base < 0) base += MOD;
            while (exp > 0) {
                if (exp & 1) res = (res * base) % MOD;
                base = (base * base) % MOD;
                exp >>= 1;
            }
            inv = res;
        }

        for (int row = col + 1; row < n; ++row) {
            if (A[row][col] == 0) continue;
            long long factor = (A[row][col] * inv) % MOD;
            for (int j = col; j < n; ++j) {
                A[row][j] = (A[row][j] - factor * A[col][j]) % MOD;
                if (A[row][j] < 0) A[row][j] += MOD;
            }
        }
    }
    for (int i = 0; i < (int)A.size(); ++i) {
        det = (det * (A[i][i] % MOD + MOD)) % MOD;
    }
    if (sign == -1) {
        det = (MOD - det) % MOD;
    }
    return det;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong(1LL, 1000000000LL, "a_i");
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    vector<int> pi(n);
    vector<char> used(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pi[i] = inf.readInt(1, n, "pi_i");
        ensuref(!used[pi[i]], "pi must be a permutation, duplicate value %d at position %d",
                pi[i], i + 1);
        used[pi[i]] = 1;
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    // Global property check for small n: directly build A and verify determinant modulo MOD
    if (n <= 7) {
        vector<vector<long long>> A(n, vector<long long>(n));
        // First row: a
        for (int j = 0; j < n; ++j) {
            A[0][j] = a[j] % MOD;
        }
        // Precompute permutation matrix P for π
        vector<vector<long long>> P(n, vector<long long>(n, 0));
        for (int j = 0; j < n; ++j) {
            // column j is e_{pi_j}
            P[pi[j] - 1][j] = 1;
        }
        // Each next row is previous row * P
        for (int i = 1; i < n; ++i) {
            vector<long long> row(n, 0);
            for (int j = 0; j < n; ++j) {
                // row[j] = sum_k A[i-1][k] * P[k][j]
                long long v = 0;
                for (int k = 0; k < n; ++k) {
                    if (P[k][j])
                        v = (v + A[i - 1][k]) % MOD;
                }
                row[j] = v;
            }
            A[i] = row;
        }

        long long d = detMod(A);
        // Determinant always exists; only modular value matters.
        // We just ensure it's a valid mod result.
        ensuref(0 <= d && d < MOD, "determinant modulo out of range");
    }

    inf.readEof();
}
