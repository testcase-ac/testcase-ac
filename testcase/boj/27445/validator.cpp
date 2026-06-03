#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int m = inf.readInt(1, 50, "M");
    inf.readEoln();

    vector<vector<int>> distance(n + 1, vector<int>(m + 1, -1));
    int maxDistance = n + m - 2;

    for (int i = 1; i < n; ++i) {
        distance[i][1] = inf.readInt(0, maxDistance, "d_i_1");
        inf.readEoln();
    }

    for (int j = 1; j <= m; ++j) {
        if (j > 1) {
            inf.readSpace();
        }
        distance[n][j] = inf.readInt(0, maxDistance, "d_N_j");
    }
    inf.readEoln();
    inf.readEof();

    int candidates = 0;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            bool ok = true;
            for (int i = 1; i < n; ++i) {
                ok &= abs(r - i) + abs(c - 1) == distance[i][1];
            }
            for (int j = 1; j <= m; ++j) {
                ok &= abs(r - n) + abs(c - j) == distance[n][j];
            }
            candidates += ok;
        }
    }

    ensuref(candidates == 1, "expected exactly one matching hidden cell, found %d", candidates);
}
