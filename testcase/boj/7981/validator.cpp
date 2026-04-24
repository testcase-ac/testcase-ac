#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of devices
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    // Sum of all r_i must not exceed 1e6
    long long sumR = 0;

    for (int i = 1; i <= n; i++) {
        // Read u_i, z_i, r_i
        long long u = inf.readLong(1LL, 1000000000LL, ("u_" + to_string(i)).c_str());
        inf.readSpace();
        long long z = inf.readLong(1LL, 1000000000LL, ("z_" + to_string(i)).c_str());
        // Constraint: u_i < z_i
        ensuref(u < z,
                "Constraint violated: u_%d < z_%d required, but got u_%d=%lld, z_%d=%lld",
                i, i, i, u, i, z);

        inf.readSpace();
        // r_i is at least 1, and sum of all r_i <= 1e6
        int r = inf.readInt(1, 1000000, ("r_" + to_string(i)).c_str());
        sumR += r;
        ensuref(sumR <= 1000000LL,
                "Sum of r_i up to index %d exceeds 1e6: sumR=%lld", i, sumR);

        // Read the list g_i,1 ... g_i,r_i
        for (int j = 1; j <= r; j++) {
            inf.readSpace();
            int g = inf.readInt(1, n, ("g_" + to_string(i) + "_" + to_string(j)).c_str());
            (void)g; // value is validated by readInt
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
