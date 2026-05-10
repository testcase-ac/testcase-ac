#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 300;
    const int Q_MAX = 500000;
    const int D_MAX = 170324;

    int N = inf.readInt(2, N_MAX, "N");
    inf.readSpace();
    int Q = inf.readInt(1, Q_MAX, "Q");
    inf.readEoln();

    // Read adjacency matrix D
    vector<vector<int>> D(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        // Read row i
        for (int j = 0; j < N; ++j) {
            D[i][j] = inf.readInt(0, D_MAX, "D_ij");
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    // Check symmetry and diagonal zero conditions
    for (int i = 0; i < N; ++i) {
        ensuref(D[i][i] == 0, "Diagonal element D[%d,%d] must be 0, found %d", i+1, i+1, D[i][i]);
        for (int j = i + 1; j < N; ++j) {
            ensuref(D[i][j] == D[j][i],
                    "Matrix must be symmetric: D[%d,%d]=%d but D[%d,%d]=%d",
                    i+1, j+1, D[i][j], j+1, i+1, D[j][i]);
        }
    }

    // Read queries
    for (int qi = 0; qi < Q; ++qi) {
        long long C = inf.readLong(1LL, (long long)N + 1, "C");
        inf.readSpace();
        int s = inf.readInt(1, N, "s");
        inf.readSpace();
        int e = inf.readInt(1, N, "e");
        inf.readEoln();
    }

    inf.readEof();
}
