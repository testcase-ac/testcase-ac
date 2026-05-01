#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

double compute_det(vector<vector<double>> a) {
    int n = a.size();
    double det = 1;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++)
            if (fabs(a[j][i]) > fabs(a[pivot][i]))
                pivot = j;
        if (fabs(a[pivot][i]) < 1e-9) return 0;
        if (pivot != i) {
            swap(a[pivot], a[i]);
            det = -det;
        }
        det *= a[i][i];
        double div = a[i][i];
        for (int j = i + 1; j < n; j++) {
            double factor = a[j][i] / div;
            for (int k = i; k < n; k++)
                a[j][k] -= factor * a[i][k];
        }
    }
    return det;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of variables
    int N = rnd.next(2, 6);
    // Generate solution vector x with values in [1,15]
    vector<int> x(N);
    for (int i = 0; i < N; i++) {
        double p = rnd.next();
        if (p < 0.3) {
            x[i] = rnd.wnext(15, -1) + 1;
        } else if (p < 0.6) {
            x[i] = rnd.wnext(15, 1) + 1;
        } else {
            x[i] = rnd.next(1, 15);
        }
    }
    vector<vector<int>> A;
    vector<int> B(N);
    // Build an invertible matrix A with entries in [1,10]
    while (true) {
        A.assign(N, vector<int>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                double p = rnd.next();
                if (p < 0.3) {
                    A[i][j] = rnd.wnext(10, -1) + 1;
                } else if (p < 0.6) {
                    A[i][j] = rnd.wnext(10, 1) + 1;
                } else {
                    A[i][j] = rnd.next(1, 10);
                }
            }
        }
        // Check determinant
        vector<vector<double>> Ad(N, vector<double>(N));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                Ad[i][j] = A[i][j];
        if (fabs(compute_det(Ad)) > 1e-6) break;
    }
    // Compute constants B = A * x, guaranteed <= 1000
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++)
            sum += A[i][j] * x[j];
        B[i] = sum;
    }
    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        vector<int> row = A[i];
        row.push_back(B[i]);
        println(row);
    }
    return 0;
}
