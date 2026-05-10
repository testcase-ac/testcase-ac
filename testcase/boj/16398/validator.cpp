#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXT = 100000; // default max test cases if multiple, but here it's single-case

    // Single test case problem (no T in statement)
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    const int MAXC = 100000000;
    const int MINC = 1;

    // Read N x N matrix
    vector<vector<long long>> c(n, vector<long long>(n));

    for (int i = 0; i < n; ++i) {
        // Read entire row as ints
        vector<int> row = inf.readInts(n, 0, MAXC, "C_ij");
        inf.readEoln();

        for (int j = 0; j < n; ++j) {
            c[i][j] = row[j];
        }
    }

    // Validate matrix properties:
    // 1) C_ii = 0
    // 2) For i != j, C_ij in [1, MAXC]
    // 3) C_ij = C_ji (symmetry)
    for (int i = 0; i < n; ++i) {
        ensuref(c[i][i] == 0, "Diagonal element C_%d%d must be 0, found %lld", i + 1, i + 1, c[i][i]);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            ensuref(c[i][j] >= MINC && c[i][j] <= MAXC,
                    "Off-diagonal element C_%d%d must be in [%d,%d], found %lld",
                    i + 1, j + 1, MINC, MAXC, c[i][j]);
            ensuref(c[i][j] == c[j][i],
                    "Matrix must be symmetric: C_%d%d (%lld) != C_%d%d (%lld)",
                    i + 1, j + 1, c[i][j], j + 1, i + 1, c[j][i]);
        }
    }

    // Optional global property: compute MST cost to ensure no overflow and that
    // the claimed "answer always exists" holds (complete graph with positive weights).
    // We'll run Prim's algorithm in O(n^2).
    if (n >= 1) {
        const long long INF = (1LL << 62);
        vector<long long> dist(n, INF);
        vector<char> used(n, 0);
        dist[0] = 0;
        long long total = 0;

        for (int it = 0; it < n; ++it) {
            int v = -1;
            for (int i = 0; i < n; ++i) {
                if (!used[i] && (v == -1 || dist[i] < dist[v])) v = i;
            }
            // In a complete graph with positive weights, this must always find a vertex
            ensuref(v != -1, "MST computation failed to find next vertex at iteration %d", it);
            used[v] = 1;
            total += dist[v];

            for (int to = 0; to < n; ++to) {
                if (!used[to] && c[v][to] < dist[to]) {
                    dist[to] = c[v][to];
                }
            }
        }

        // Check that total cost is within safe bounds (no overflow)
        // Max possible MST cost is (n-1) * MAXC, with n<=1000 => <= 999 * 1e8 < 1e11
        long long maxPossible = (long long)(n - 1) * (long long)MAXC;
        ensuref(total >= 0 && total <= maxPossible,
                "Computed MST cost %lld is out of expected range [0,%lld]",
                total, maxPossible);
    }

    inf.readEof();
}
