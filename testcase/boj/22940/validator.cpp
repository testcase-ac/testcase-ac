#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Helper function to compute determinant of a matrix (for small N)
double determinant(vector<vector<double>> mat) {
    int n = mat.size();
    double det = 1.0;
    for (int i = 0; i < n; ++i) {
        // Find pivot
        int pivot = i;
        for (int j = i + 1; j < n; ++j)
            if (fabs(mat[j][i]) > fabs(mat[pivot][i]))
                pivot = j;
        if (fabs(mat[pivot][i]) < 1e-9)
            return 0.0;
        if (i != pivot) {
            swap(mat[i], mat[pivot]);
            det = -det;
        }
        det *= mat[i][i];
        for (int j = i + 1; j < n; ++j) {
            double f = mat[j][i] / mat[i][i];
            for (int k = i; k < n; ++k)
                mat[j][k] -= f * mat[i][k];
        }
    }
    return det;
}

// Helper function to solve Ax = b for small N, returns vector of doubles
vector<double> solve_linear(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    vector<vector<double>> mat(n, vector<double>(n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            mat[i][j] = A[i][j];
        mat[i][n] = b[i];
    }
    // Gaussian elimination
    for (int i = 0; i < n; ++i) {
        // Find pivot
        int pivot = i;
        for (int j = i + 1; j < n; ++j)
            if (fabs(mat[j][i]) > fabs(mat[pivot][i]))
                pivot = j;
        ensuref(fabs(mat[pivot][i]) > 1e-9, "System is singular at row %d", i);
        if (i != pivot)
            swap(mat[i], mat[pivot]);
        // Eliminate
        for (int j = i + 1; j < n; ++j) {
            double f = mat[j][i] / mat[i][i];
            for (int k = i; k <= n; ++k)
                mat[j][k] -= f * mat[i][k];
        }
    }
    // Back substitution
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = mat[i][n];
        for (int j = i + 1; j < n; ++j)
            x[i] -= mat[i][j] * x[j];
        x[i] /= mat[i][i];
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 6, "N");
    inf.readEoln();

    vector<vector<int>> A(N, vector<int>(N));
    vector<int> B(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = inf.readInt(1, 10, "A_ij");
            if (j < N - 1)
                inf.readSpace();
        }
        inf.readSpace();
        B[i] = inf.readInt(1, 1000, "B_i");
        inf.readEoln();
    }

    // Check: The system has a unique solution, and all variables are natural numbers (1..100)
    // This is a global property and must be validated.

    // Convert to double for computation
    vector<vector<double>> Ad(N, vector<double>(N));
    vector<double> Bd(N);
    for (int i = 0; i < N; ++i) {
        Bd[i] = B[i];
        for (int j = 0; j < N; ++j)
            Ad[i][j] = A[i][j];
    }

    // Check determinant is nonzero (unique solution)
    double det = determinant(Ad);
    ensuref(fabs(det) > 1e-8, "Coefficient matrix is singular, system does not have a unique solution (det=%.10lf)", det);

    // Solve the system
    vector<double> x = solve_linear(Ad, Bd);

    // Check all variables are natural numbers in [1, 100], and are integer-valued
    for (int i = 0; i < N; ++i) {
        double xi = x[i];
        double xi_round = round(xi);
        ensuref(fabs(xi - xi_round) < 1e-6, "Variable x_%d is not integer: %.10lf", i + 1, xi);
        int xi_int = (int)(xi_round + 0.5);
        ensuref(1 <= xi_int && xi_int <= 100, "Variable x_%d = %d is not in [1, 100]", i + 1, xi_int);
    }

    inf.readEof();
}
