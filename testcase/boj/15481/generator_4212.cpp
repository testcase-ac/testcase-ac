#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices
    int N = rnd.next(2, 10);

    // Compute how many extra edges we can add (limit total M <= 20)
    int maxPossible = N * (N - 1) / 2;
    int maxExtraByConnectivity = maxPossible - (N - 1);
    int capExtra    = min(maxExtraByConnectivity, max(0, 20 - (N - 1)));
    int extra       = capExtra > 0 ? rnd.next(0, capExtra) : 0;
    int M           = (N - 1) + extra;

    // Choose a maximum weight from a small set for diversity
    vector<int> weightOpts = {10, 100, 1000};
    int hiW = rnd.any(weightOpts);

    // Skew factors for tree and extra edges
    int skewTree  = rnd.next(-1, 1);
    int skewExtra = rnd.next(-1, 1);

    // Build a random spanning tree first
    vector<tuple<int,int,int>> edges;
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    for (int v = 2; v <= N; ++v) {
        int u = rnd.next(1, v - 1);
        used[u][v] = used[v][u] = true;
        int w = rnd.wnext(hiW, skewTree) + 1;  // weight in [1..hiW]
        edges.emplace_back(u, v, w);
    }

    // Prepare candidate extra edges
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (!used[i][j]) {
                cand.emplace_back(i, j);
            }
        }
    }
    shuffle(cand.begin(), cand.end());
    for (int i = 0; i < extra; ++i) {
        int u = cand[i].first;
        int v = cand[i].second;
        int w = rnd.wnext(hiW, skewExtra) + 1;
        edges.emplace_back(u, v, w);
    }

    // Shuffle all edges for random order
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, M);
    for (auto &e : edges) {
        println(get<0>(e), get<1>(e), get<2>(e));
    }

    return 0;
}
