#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and s
    int n = inf.readInt(0, 10000, "n");
    inf.readSpace();
    int s = inf.readInt(1, 100, "s");
    inf.readEoln();

    // Read holes
    vector<long long> r(n), x(n), y(n), z(n);
    for (int i = 0; i < n; i++) {
        r[i] = inf.readInt(1, 100000, "r_i");
        inf.readSpace();
        x[i] = inf.readInt(1, 100000, "x_i");
        inf.readSpace();
        y[i] = inf.readInt(1, 100000, "y_i");
        inf.readSpace();
        z[i] = inf.readInt(1, 100000, "z_i");
        inf.readEoln();

        // Hole must be fully inside [0,100000]^3
        ensuref(r[i] <= x[i],
                "Hole %d: x_i (%lld) is less than r_i (%lld)", i, x[i], r[i]);
        ensuref(x[i] + r[i] <= 100000,
                "Hole %d: x_i + r_i = %lld exceeds 100000", i, x[i] + r[i]);
        ensuref(r[i] <= y[i],
                "Hole %d: y_i (%lld) is less than r_i (%lld)", i, y[i], r[i]);
        ensuref(y[i] + r[i] <= 100000,
                "Hole %d: y_i + r_i = %lld exceeds 100000", i, y[i] + r[i]);
        ensuref(r[i] <= z[i],
                "Hole %d: z_i (%lld) is less than r_i (%lld)", i, z[i], r[i]);
        ensuref(z[i] + r[i] <= 100000,
                "Hole %d: z_i + r_i = %lld exceeds 100000", i, z[i] + r[i]);
    }

    // Check that holes do not overlap (they may touch)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long dx = x[i] - x[j];
            long long dy = y[i] - y[j];
            long long dz = z[i] - z[j];
            long long dist2 = dx*dx + dy*dy + dz*dz;
            long long sum = r[i] + r[j];
            long long need = sum * sum;
            ensuref(dist2 >= need,
                    "Holes %d and %d overlap: center distance^2 = %lld, but (r_i+r_j)^2 = %lld",
                    i, j, dist2, need);
        }
    }

    inf.readEof();
    return 0;
}
