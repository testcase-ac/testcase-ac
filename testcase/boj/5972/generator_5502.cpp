#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of barns
    int N = rnd.next(2, 10);
    // Maximum possible edges
    int maxEdges = N * (N - 1) / 2;
    // Extra edges beyond a spanning tree, up to N
    int extra = rnd.next(0, min(maxEdges - (N - 1), N));
    int M = (N - 1) + extra;

    // Build a random spanning tree to ensure connectivity
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    // Keep node 1 at front, shuffle the rest
    shuffle(perm.begin() + 1, perm.end());
    vector<vector<bool>> used(N + 1, vector<bool>(N + 1, false));
    vector<tuple<int,int,int>> edges;
    for (int i = 1; i < N; i++) {
        int u = perm[i];
        int v = perm[rnd.next(0, i - 1)];
        used[u][v] = used[v][u] = true;
        edges.emplace_back(u, v, 0); // weight placeholder
    }

    // Collect non-tree edge candidates
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (!used[i][j]) cand.emplace_back(i, j);
        }
    }
    shuffle(cand.begin(), cand.end());
    // Add extra edges
    for (int i = 0; i < extra; i++) {
        int u = cand[i].first;
        int v = cand[i].second;
        used[u][v] = used[v][u] = true;
        edges.emplace_back(u, v, 0);
    }

    // Hyper-parameter: choose maximum weight bound from pool
    vector<int> maxWpool = {5, 10, 50};
    int maxW = rnd.any(maxWpool);
    // Probability for zero-weight edges
    double zeroProb = rnd.next();

    // Assign weights to all edges
    for (auto &e : edges) {
        int w;
        if (rnd.next() < zeroProb)
            w = 0;
        else
            w = rnd.next(1, maxW);
        get<2>(e) = w;
    }

    // Shuffle edges for output
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, M);
    for (auto &e : edges) {
        println(get<0>(e), get<1>(e), get<2>(e));
    }

    return 0;
}
