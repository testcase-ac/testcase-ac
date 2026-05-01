#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
#include <numeric>
using namespace std;

int randomWeight() {
    int t = rnd.next(0, 9);
    if (t == 0) return 1;                 // very small
    if (t == 1) return 10000;             // very large
    if (t == 2) return rnd.next(2, 5);
    if (t == 3) return rnd.next(6, 20);
    if (t <= 6) return rnd.next(21, 100);
    return rnd.next(101, 1000);           // keep moderate for readability
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with some variety, but small enough to be readable
    int type = rnd.next(1, 6);
    int N;
    if (type == 1) N = rnd.next(2, 4);        // very small
    else if (type == 2) N = rnd.next(3, 6);   // small
    else if (type == 3) N = rnd.next(5, 8);   // small-medium
    else N = rnd.next(8, 12);                 // medium

    // Choose K (number of plants) with bias towards interesting cases
    int mode = rnd.next(0, 4);
    int K;
    if (mode == 0) K = 1;                     // single plant (classic MST)
    else if (mode == 1) K = min(2, N);        // two plants
    else if (mode == 2) K = min(3, N);        // few plants
    else if (mode == 3) K = N;                // every city has a plant
    else K = rnd.next(1, N);                  // fully random
    if (K < 1) K = 1;
    if (K > N) K = N;

    // Choose which cities have plants
    vector<int> cities(N);
    iota(cities.begin(), cities.end(), 1);
    shuffle(cities.begin(), cities.end());
    vector<int> plants(cities.begin(), cities.begin() + K);

    // owner[i] = plant city that this city should be connected to (for base forest)
    vector<int> owner(N + 1, 0);
    for (int p : plants) owner[p] = p;
    for (int i = 1; i <= N; ++i) {
        if (owner[i] == 0) {
            owner[i] = rnd.any(plants);
        }
    }

    // Group nodes by their assigned plant
    vector<vector<int>> groups(N + 1);
    for (int i = 1; i <= N; ++i) {
        groups[owner[i]].push_back(i);
    }

    // Adjacency matrix to avoid multiple edges
    vector<vector<int>> adj(N + 1, vector<int>(N + 1, 0));
    vector<tuple<int,int,int>> edges;

    auto tryAddEdge = [&](int u, int v, int w) {
        if (u == v) return;
        if (adj[u][v] != 0) return;
        adj[u][v] = adj[v][u] = w;
        edges.emplace_back(u, v, w);
    };

    // Build a tree inside each group so every city can reach its plant
    for (int p : plants) {
        auto &nodes = groups[p];
        if (nodes.empty()) continue;
        // Ensure plant is first
        auto it = find(nodes.begin(), nodes.end(), p);
        if (it != nodes.end()) {
            swap(nodes[0], *it);
        }
        for (int j = 1; j < (int)nodes.size(); ++j) {
            int parentIndex = rnd.next(0, j - 1);
            int u = nodes[parentIndex];
            int v = nodes[j];
            int w = randomWeight();
            tryAddEdge(u, v, w);
        }
    }

    int maxPossiblePairs = N * (N - 1) / 2;
    int maxTotalEdges = min(30, maxPossiblePairs); // keep test small & readable

    // Add some "tricky" edges involving power plants to catch wrong solutions
    if ((int)edges.size() < maxTotalEdges && K >= 2) {
        vector<int> plantsShuffled = plants;
        shuffle(plantsShuffled.begin(), plantsShuffled.end());
        int p1 = plantsShuffled[0];
        int p2 = plantsShuffled[1];

        int trickyType = rnd.next(0, 2); // 0: direct plant edge, 1: via non-plant
        if (trickyType == 0) {
            // Direct cheap edge between two plants
            int w = rnd.next(1, 3);
            tryAddEdge(p1, p2, w);
        } else {
            // Path p1 - x - p2 with cheap edges, if a non-plant exists
            vector<int> nonPlants;
            vector<bool> isPlant(N + 1, false);
            for (int p : plants) isPlant[p] = true;
            for (int i = 1; i <= N; ++i)
                if (!isPlant[i]) nonPlants.push_back(i);

            if (!nonPlants.empty()) {
                int x = rnd.any(nonPlants);
                int w1 = rnd.next(1, 3);
                int w2 = rnd.next(1, 3);
                if ((int)edges.size() < maxTotalEdges) tryAddEdge(p1, x, w1);
                if ((int)edges.size() < maxTotalEdges) tryAddEdge(x, p2, w2);
            } else {
                // Fallback: direct edge if no non-plant
                int w = rnd.next(1, 3);
                tryAddEdge(p1, p2, w);
            }
        }
    }

    // Decide how many extra random edges to add
    int baseM = (int)edges.size();
    int maxExtra = min(maxTotalEdges - baseM, maxPossiblePairs - baseM);
    int extra = 0;
    if (maxExtra > 0) {
        int style = rnd.next(0, 2);
        if (style == 0) {
            extra = rnd.next(0, maxExtra);
        } else if (style == 1) {
            int lo = max(0, maxExtra / 2);
            extra = rnd.next(lo, maxExtra);
        } else {
            extra = maxExtra;
        }
    }
    int targetM = baseM + extra;

    // Add random extra edges
    int tries = 0;
    while ((int)edges.size() < targetM && tries < 1000) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        if (u == v || adj[u][v] != 0) {
            ++tries;
            continue;
        }
        int w = randomWeight();
        adj[u][v] = adj[v][u] = w;
        edges.emplace_back(u, v, w);
    }

    // Ensure at least one edge (M >= 1)
    if (edges.empty()) {
        int u = 1, v = 2;
        int w = randomWeight();
        adj[u][v] = adj[v][u] = w;
        edges.emplace_back(u, v, w);
    }

    // Shuffle edges for randomness
    shuffle(edges.begin(), edges.end());

    // Output
    int M = (int)edges.size();
    println(N, M, K);
    sort(plants.begin(), plants.end());
    println(plants);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }

    return 0;
}
