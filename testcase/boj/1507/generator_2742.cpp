#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameters
    int N = rnd.next(2, 10);
    int W = rnd.next(1, 20);          // max edge weight
    bool make_bad = (N >= 3 && rnd.next(0, 9) == 0); // ~10% chance of impossible case

    // Generate a random tree on nodes 1..N
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());
    vector<pair<int,int>> edges;
    vector<int> weights;
    for (int i = 1; i < N; i++) {
        int u = perm[i];
        int v = perm[rnd.next(0, i-1)];
        edges.emplace_back(u, v);
        weights.push_back(rnd.next(1, W));
    }

    // Compute all-pairs distances by Floyd-Warshall
    const int INF = 1000000000;
    vector<vector<int>> d(N+1, vector<int>(N+1, INF));
    for (int i = 1; i <= N; i++) d[i][i] = 0;
    for (int i = 0; i < (int)edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        int w = weights[i];
        d[u][v] = d[v][u] = w;
    }
    for (int k = 1; k <= N; k++)
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];

    // Optionally corrupt one distance to make it impossible
    if (make_bad) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        while (v == u) v = rnd.next(1, N);
        int k = rnd.next(1, N);
        while (k == u || k == v) k = rnd.next(1, N);
        int sum = d[u][k] + d[k][v];
        if (sum < INF/2) {
            int add = rnd.next(1, 5);
            int nv = sum + add;
            if (nv <= 2500) {
                d[u][v] = d[v][u] = nv;
            }
        }
    }

    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        vector<int> row(N);
        for (int j = 1; j <= N; j++) row[j-1] = d[i][j];
        println(row);
    }
    return 0;
}
