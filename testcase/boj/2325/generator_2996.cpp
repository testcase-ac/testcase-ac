#include "testlib.h"
#include <algorithm>
#include <vector>
#include <numeric>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes, at least 3 to form a simple cycle
    int N = rnd.next(3, 10);
    // Maximum edges capped for hand-checkable size
    int Mmax = min(N * (N - 1) / 2, 20);
    // At least N edges to build a cycle, at most Mmax
    int M = rnd.next(N, Mmax);

    // Create a random permutation of nodes [1..N]
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    // Ensure node 1 is start and node N is end
    for (int i = 0; i < N; i++)
        if (nodes[i] == 1) { swap(nodes[i], nodes[0]); break; }
    for (int i = 0; i < N; i++)
        if (nodes[i] == N) { swap(nodes[i], nodes[N-1]); break; }

    // Build a simple cycle through all nodes
    vector<pair<int,int>> cycle;
    for (int i = 0; i + 1 < N; i++)
        cycle.emplace_back(nodes[i], nodes[i+1]);
    cycle.emplace_back(nodes[N-1], nodes[0]);

    // Collect remaining candidate edges (no multi-edges, undirected)
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            bool inCycle = false;
            for (auto &e : cycle) {
                if ((e.first == i && e.second == j) ||
                    (e.first == j && e.second == i)) {
                    inCycle = true;
                    break;
                }
            }
            if (!inCycle)
                cand.emplace_back(i, j);
        }
    }
    shuffle(cand.begin(), cand.end());

    int extra = M - N;
    vector<pair<int,int>> edges_uv = cycle;
    for (int i = 0; i < extra; i++)
        edges_uv.push_back(cand[i]);

    // Weight distribution hyper-parameters
    int typeMain = rnd.next(0, 2);
    int typeExtra = rnd.next(0, 2);
    auto genW = [&](int tp) {
        if (tp == 0) return rnd.next(1, 10);
        if (tp == 1) return rnd.wnext(10, 2) + 1;   // bias toward larger
        return rnd.wnext(10, -2) + 1;              // bias toward smaller
    };

    // Assign weights: cycle edges use typeMain, extras use typeExtra
    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < N; i++) {
        auto &e = cycle[i];
        edges.emplace_back(e.first, e.second, genW(typeMain));
    }
    for (int i = N; i < M; i++) {
        auto &e = edges_uv[i];
        edges.emplace_back(e.first, e.second, genW(typeExtra));
    }

    // Shuffle final edge list for randomness
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, M);
    for (auto &t : edges) {
        int u, v, w;
        tie(u, v, w) = t;
        println(u, v, w);
    }

    return 0;
}
