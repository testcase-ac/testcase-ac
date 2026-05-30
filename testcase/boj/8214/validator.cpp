#include "testlib.h"

#include <vector>
using namespace std;

static bool hasVertexCover(vector<vector<int>>& adj, vector<char>& removed, int budget) {
    int bestU = -1;
    int bestV = -1;
    int bestDegree = -1;

    for (int u = 1; u < (int)adj.size(); ++u) {
        if (removed[u]) {
            continue;
        }

        int degree = 0;
        int firstNeighbor = -1;
        for (int v : adj[u]) {
            if (!removed[v]) {
                ++degree;
                if (firstNeighbor == -1) {
                    firstNeighbor = v;
                }
            }
        }

        if (degree > bestDegree) {
            bestDegree = degree;
            bestU = u;
            bestV = firstNeighbor;
        }
    }

    if (bestDegree <= 0) {
        return true;
    }
    if (budget == 0) {
        return false;
    }

    removed[bestU] = true;
    if (hasVertexCover(adj, removed, budget - 1)) {
        removed[bestU] = false;
        return true;
    }
    removed[bestU] = false;

    removed[bestV] = true;
    if (hasVertexCover(adj, removed, budget - 1)) {
        removed[bestV] = false;
        return true;
    }
    removed[bestV] = false;

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 3000, "n");
    ensuref(n % 3 == 0, "n must be divisible by 3, found %d", n);
    inf.readSpace();

    int cliqueSize = 2 * n / 3;
    int minM = cliqueSize * (cliqueSize - 1) / 2;
    int maxM = n * (n - 1) / 2;
    int m = inf.readInt(minM, maxM, "m");
    inf.readEoln();

    vector<vector<bool>> seen(n + 1, vector<bool>(n + 1, false));
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a < b, "edge %d must satisfy a_i < b_i, found %d %d", i, a, b);
        ensuref(!seen[a][b], "duplicate edge %d %d at line %d", a, b, i + 1);
        seen[a][b] = true;
    }

    inf.readEof();

    vector<vector<int>> complement(n + 1);
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!seen[a][b]) {
                complement[a].push_back(b);
                complement[b].push_back(a);
            }
        }
    }

    vector<char> removed(n + 1, false);
    ensuref(hasVertexCover(complement, removed, n / 3),
            "graph must contain a clique of size 2n/3");
}
