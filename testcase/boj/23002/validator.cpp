#include "testlib.h"

#include <numeric>
#include <vector>
using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 500, "N");
        inf.readEoln();

        vector<vector<int>> a(n, vector<int>(n));
        vector<int> knownRowXor(n, 0), knownColXor(n, 0);
        Dsu dsu(2 * n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                a[i][j] = inf.readInt(-1, 1, "A_ij");
                if (a[i][j] == -1) {
                    dsu.unite(i, n + j);
                } else {
                    knownRowXor[i] ^= a[i][j];
                    knownColXor[j] ^= a[i][j];
                }
            }
            inf.readEoln();
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                int expectedLow = a[i][j] == -1 ? 1 : 0;
                int expectedHigh = a[i][j] == -1 ? 1000 : 0;
                inf.readInt(expectedLow, expectedHigh, "B_ij");
            }
            inf.readEoln();
        }

        vector<int> rowNeed(n), colNeed(n);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            int r = inf.readInt(0, 1, "R_i");
            rowNeed[i] = r ^ knownRowXor[i];
        }
        inf.readEoln();

        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int c = inf.readInt(0, 1, "C_j");
            colNeed[j] = c ^ knownColXor[j];
        }
        inf.readEoln();

        vector<int> componentRowXor(2 * n, 0), componentColXor(2 * n, 0);
        for (int i = 0; i < n; ++i) {
            componentRowXor[dsu.find(i)] ^= rowNeed[i];
        }
        for (int j = 0; j < n; ++j) {
            componentColXor[dsu.find(n + j)] ^= colNeed[j];
        }
        for (int v = 0; v < 2 * n; ++v) {
            if (dsu.find(v) == v) {
                ensuref(componentRowXor[v] == componentColXor[v],
                        "checksum constraints are infeasible in component %d", v);
            }
        }
    }

    inf.readEof();
}
