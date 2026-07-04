#include "testlib.h"

#include <algorithm>
#include <limits>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long INF = numeric_limits<long long>::max() / 4;

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100, "N");
        inf.readSpace();
        int q = inf.readInt(1, 100, "Q");
        inf.readEoln();

        vector<long long> endurance(n);
        for (int i = 0; i < n; ++i) {
            endurance[i] = inf.readLong(1LL, 1000000000LL, "E_i");
            inf.readSpace();
            inf.readLong(1LL, 1000LL, "S_i");
            inf.readEoln();
        }

        vector<vector<long long>> dist(n, vector<long long>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                dist[i][j] = inf.readLong(-1LL, 1000000000LL, "D_ij");
                if (i == j) {
                    ensuref(dist[i][j] == -1, "D_%d_%d must be -1", i + 1, j + 1);
                } else {
                    ensuref(dist[i][j] != 0, "D_%d_%d must not be 0", i + 1, j + 1);
                }
            }
            inf.readEoln();
        }

        vector<pair<int, int>> queries;
        queries.reserve(q);
        set<pair<int, int>> seenQueries;
        for (int i = 0; i < q; ++i) {
            int u = inf.readInt(1, n, "U_k");
            inf.readSpace();
            int v = inf.readInt(1, n, "V_k");
            inf.readEoln();

            ensuref(u != v, "query %d has equal endpoints %d", i + 1, u);
            ensuref(seenQueries.insert({u, v}).second,
                    "query %d repeats ordered pair (%d, %d)", i + 1, u, v);
            queries.push_back({u - 1, v - 1});
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] == -1) {
                    dist[i][j] = INF;
                }
            }
            dist[i][i] = 0;
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] == INF || dist[k][j] == INF) {
                        continue;
                    }
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        vector<vector<char>> canDeliver(n, vector<char>(n, false));
        for (int i = 0; i < n; ++i) {
            canDeliver[i][i] = true;
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] <= endurance[i]) {
                    canDeliver[i][j] = true;
                }
            }
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    canDeliver[i][j] =
                        canDeliver[i][j] || (canDeliver[i][k] && canDeliver[k][j]);
                }
            }
        }

        for (int i = 0; i < q; ++i) {
            int u = queries[i].first;
            int v = queries[i].second;
            ensuref(canDeliver[u][v], "query %d from %d to %d cannot be accomplished",
                    i + 1, u + 1, v + 1);
        }
    }

    inf.readEof();
}
