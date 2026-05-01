#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(5, 12);
    // Maximum possible extra edges beyond a spanning tree
    int C = N * (N - 1) / 2;
    int maxExtra = max(0, C - (N - 1));

    // Hyper-parameter for density: -1 sparse, 0 medium, +1 dense
    int densType = rnd.next(0, 2) - 1;
    int extras;
    if (maxExtra == 0) {
        extras = 0;
    } else if (densType < 0) {
        // sparse: minimal extra edges
        extras = rnd.wnext(maxExtra + 1, -1);
    } else if (densType > 0) {
        // dense: many extra edges
        extras = rnd.wnext(maxExtra + 1, 1);
    } else {
        // medium: uniform
        extras = rnd.next(0, maxExtra);
    }
    int M = (N - 1) + extras;

    // Build a random spanning tree first
    vector<tuple<int,int,int>> edges;
    vector<vector<bool>> used(N + 1, vector<bool>(N + 1, false));
    for (int i = 2; i <= N; i++) {
        int j = rnd.next(1, i - 1);
        int w = rnd.next(1, 1000);
        edges.emplace_back(i, j, w);
        used[i][j] = used[j][i] = true;
    }
    // Collect remaining candidate edges
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (!used[i][j]) cand.emplace_back(i, j);
        }
    }
    // Shuffle and take 'extras' edges
    shuffle(cand.begin(), cand.end());
    for (int i = 0; i < extras; i++) {
        auto [u, v] = cand[i];
        int w = rnd.next(1, 1000);
        edges.emplace_back(u, v, w);
    }
    // Final shuffle of all edges
    shuffle(edges.begin(), edges.end());

    // Hyper-parameters for festivals
    int K;
    int r = rnd.next(1, 3);
    if (r == 1) K = 1;
    else if (r == 2) K = N;
    else K = rnd.next(1, N);

    vector<int> fest(N);
    iota(fest.begin(), fest.end(), 1);
    shuffle(fest.begin(), fest.end());
    fest.resize(K);

    // Number of queries
    int Q = rnd.next(1, N);
    vector<pair<int,int>> queries;
    for (int i = 0; i < Q; i++) {
        int u, v;
        do {
            u = rnd.next(1, N);
            v = rnd.next(1, N);
        } while (u == v);
        queries.emplace_back(u, v);
    }

    // Output
    println(N, M, K, Q);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }
    for (int x : fest) println(x);
    for (auto &q : queries) println(q.first, q.second);

    return 0;
}
