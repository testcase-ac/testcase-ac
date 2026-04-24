#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(2, 10);
    int max_edges = N * (N - 1) / 2;

    // Decide how many extra edges beyond a spanning tree
    int hi_extra = max_edges - (N - 1) + 1; // exclusive upper bound for wnext
    int t3 = rnd.any(vector<int>{-1, 0, 1});
    int extra = rnd.wnext(hi_extra, t3);
    int M = (N - 1) + extra;

    // Build a random spanning tree to ensure connectivity
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());
    vector<pair<int,int>> tree_edges;
    for (int i = 1; i < N; i++) {
        int u = perm[i];
        int v = perm[rnd.next(0, i - 1)];
        tree_edges.emplace_back(min(u,v), max(u,v));
    }

    // Collect all possible remaining edges
    vector<pair<int,int>> candidates;
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    for (auto &e : tree_edges) {
        used[e.first][e.second] = used[e.second][e.first] = true;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (!used[i][j]) {
                candidates.emplace_back(i, j);
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    // Take extra edges
    vector<pair<int,int>> edges = tree_edges;
    for (int i = 0; i < extra && i < (int)candidates.size(); i++) {
        edges.push_back(candidates[i]);
    }
    shuffle(edges.begin(), edges.end());

    // Edge length hyper-parameter bias
    int t2 = rnd.any(vector<int>{-1, 0, 1});
    // Assign lengths
    vector<int> lengths;
    lengths.reserve(edges.size());
    for (size_t i = 0; i < edges.size(); i++) {
        int w = rnd.wnext(1000, t2) + 1; // [1..1000]
        lengths.push_back(w);
    }

    // Number of shopping malls
    int t4 = rnd.any(vector<int>{-1, 0, 1});
    int K = rnd.wnext(N, t4) + 1; // [1..N]

    // Choose distinct mall cities
    vector<int> cities(N);
    iota(cities.begin(), cities.end(), 1);
    shuffle(cities.begin(), cities.end());
    cities.resize(K);

    // Output
    println(N, M, K);
    for (int i = 0; i < M; i++) {
        println(edges[i].first, edges[i].second, lengths[i]);
    }
    // Shopping mall cities
    for (int x : cities) {
        println(x);
    }

    return 0;
}
