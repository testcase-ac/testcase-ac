#include "testlib.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

// Compute the volume of the vase defined by f(x) = a * exp(-x^2) + b * sqrt(x), rotated around x-axis, for x in [0, h]
double compute_volume(double a, double b, double h) {
    // Use numerical integration (Simpson's rule)
    // V = pi * ∫_{x=0}^{h} (f(x))^2 dx
    const int N = 100000; // Number of intervals (even)
    double dx = h / N;
    double sum = 0.0;
    for (int i = 0; i <= N; ++i) {
        double x = dx * i;
        double fx = a * exp(-x * x) + b * (x > 0 ? sqrt(x) : 0.0);
        double term = fx * fx;
        if (i == 0 || i == N) sum += term;
        else if (i % 2 == 1) sum += 4 * term;
        else sum += 2 * term;
    }
    double integral = dx / 3.0 * sum;
    return M_PI * integral;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read V and N
    double V = inf.readDouble(1.0 + 1e-9, 1e5, "V"); // 1 < V <= 1e5
    inf.readSpace();
    int N = inf.readInt(1, 5, "N"); // 0 < N <= 5
    inf.readEoln();

    // Read N vases
    vector<double> a(N), b(N), h(N), volume(N);
    for (int i = 0; i < N; ++i) {
        a[i] = inf.readDouble(1.0, 10.0, "a");
        inf.readSpace();
        b[i] = inf.readDouble(1.0, 10.0, "b");
        inf.readSpace();
        h[i] = inf.readDouble(1.0, 10.0, "h");
        inf.readEoln();

        // Compute volume for each vase
        volume[i] = compute_volume(a[i], b[i], h[i]);
        ensuref(volume[i] > 0.0, "Volume of vase %d is not positive: %.10lf", i, volume[i]);
    }

    // Check that all pairs of vases have volume difference at least 1e-4
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            double diff = fabs(volume[i] - volume[j]);
            ensuref(diff >= 1e-4 - 1e-10, "Vase volumes too close: vases %d and %d, diff = %.10lf", i, j, diff);
        }
    }

    // Check that all vases' volumes differ from V by at least 1e-4
    for (int i = 0; i < N; ++i) {
        double diff = fabs(volume[i] - V);
        ensuref(diff >= 1e-4 - 1e-10, "Vase volume too close to V: vase %d, diff = %.10lf", i, diff);
    }

    inf.readEof();
}
