#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static vector<long double> solve(vector<vector<long double>> a, vector<long double> b) {
    int n = (int)a.size();

    for (int col = 0; col < n; ++col) {
        int pivot = col;
        for (int row = col + 1; row < n; ++row) {
            if (fabsl(a[row][col]) > fabsl(a[pivot][col])) {
                pivot = row;
            }
        }

        ensuref(fabsl(a[pivot][col]) > 1e-12L,
                "coefficient matrix is singular at column %d", col + 1);

        if (pivot != col) {
            swap(a[pivot], a[col]);
            swap(b[pivot], b[col]);
        }

        for (int row = col + 1; row < n; ++row) {
            long double factor = a[row][col] / a[col][col];
            for (int k = col; k < n; ++k) {
                a[row][k] -= factor * a[col][k];
            }
            b[row] -= factor * b[col];
        }
    }

    vector<long double> x(n);
    for (int row = n - 1; row >= 0; --row) {
        long double value = b[row];
        for (int col = row + 1; col < n; ++col) {
            value -= a[row][col] * x[col];
        }
        x[row] = value / a[row][row];
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 6, "N");
    inf.readEoln();

    vector<vector<long double>> a(n, vector<long double>(n));
    vector<long double> b(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = inf.readInt(1, 10, "A_i");
            inf.readSpace();
        }
        b[i] = inf.readInt(1, 6000, "B");
        inf.readEoln();
    }

    vector<long double> x = solve(a, b);
    for (int i = 0; i < n; ++i) {
        long double rounded = roundl(x[i]);
        ensuref(fabsl(x[i] - rounded) <= 1e-7L,
                "solution x_%d is not an integer: %.12Lf", i + 1, x[i]);
        ensuref(1.0L <= rounded && rounded <= 100.0L,
                "solution x_%d is not a natural number at most 100: %.12Lf",
                i + 1, x[i]);
    }

    inf.readEof();
}
