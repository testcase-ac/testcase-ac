#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 8);
    int maxE = N * (N - 1) / 2;
    int M = rnd.next(N - 1, maxE);

    vector<vector<bool>> adj(N + 1, vector<bool>(N + 1, false));
    vector<tuple<int, int, int>> edges;

    // Generate a random spanning tree to ensure connectivity
    vector<int> order(N);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());
    vector<int> connected;
    connected.push_back(order[0]);
    for (int i = 1; i < N; i++) {
        int v = order[i];
        int u = rnd.any(connected);
        int t = rnd.next(-1, 1);
        int w = rnd.wnext(20, t) + 1;
        edges.emplace_back(u, v, w);
        adj[u][v] = adj[v][u] = true;
        connected.push_back(v);
    }

    // Add extra random edges
    while ((int)edges.size() < M) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        if (u == v || adj[u][v]) continue;
        int t = rnd.next(-1, 1);
        int w = rnd.wnext(20, t) + 1;
        edges.emplace_back(u, v, w);
        adj[u][v] = adj[v][u] = true;
    }

    // Shuffle edges for output
    shuffle(edges.begin(), edges.end());

    // Choose total health K with variability
    int tK = rnd.next(-1, 1);
    int K = rnd.wnext(N * 20, tK) + 1;

    // Output
    println(N, M, K);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }

    return 0;
}
