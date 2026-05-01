#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N for hand-checkable sizes
    int N = rnd.next(2, 12);
    int maxEdges = N * (N - 1) / 2;
    int capEdges = min(maxEdges, 20);
    int pattern = rnd.next(0, 4);

    vector<pair<int,int>> edges;

    if (pattern == 0) {
        // Empty graph
    }
    else if (pattern == 1) {
        // Simple chain
        for (int i = 0; i + 1 < N; i++)
            edges.emplace_back(i, i + 1);
    }
    else if (pattern == 2 && N >= 4) {
        // Two parallel short paths: 0-u-N-1 and 0-v-N-1
        int u = rnd.next(1, N - 2);
        int v = rnd.next(1, N - 2);
        while (v == u) v = rnd.next(1, N - 2);
        edges.emplace_back(0, u);
        edges.emplace_back(u, N - 1);
        edges.emplace_back(0, v);
        edges.emplace_back(v, N - 1);
    }
    else if (pattern == 3) {
        // Random sparse
        int upper = max(1, capEdges/2);
        int M = rnd.next(1, upper);
        vector<pair<int,int>> all;
        for (int i = 0; i < N; i++)
            for (int j = i+1; j < N; j++)
                all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        for (int i = 0; i < M; i++)
            edges.push_back(all[i]);
    }
    else {
        // Random dense
        int lower = max(1, capEdges/2);
        int M = rnd.next(lower, capEdges);
        vector<pair<int,int>> all;
        for (int i = 0; i < N; i++)
            for (int j = i+1; j < N; j++)
                all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        for (int i = 0; i < M; i++)
            edges.push_back(all[i]);
    }

    // Shuffle edge order to vary capacities
    shuffle(edges.begin(), edges.end());

    // Output
    int M = edges.size();
    println(N, M);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
