/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small graph size for hand-checking
    int N = rnd.next(2, 10);
    int maxM = N * (N - 1) / 2;
    int M = rnd.next(N - 1, maxM);
    int K = rnd.next(1, min(20, M));

    // Prepare containers
    vector<pair<int,int>> edges;
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));

    // 1) Ensure connectivity via a random spanning tree
    for (int v = 2; v <= N; ++v) {
        int u = rnd.next(1, v - 1);
        edges.emplace_back(u, v);
        used[u][v] = used[v][u] = true;
    }

    // 2) List remaining possible edges
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (!used[i][j]) {
                cand.emplace_back(i, j);
            }
        }
    }

    // Shuffle candidates and pick extra edges
    shuffle(cand.begin(), cand.end());
    int extra = M - (N - 1);
    for (int i = 0; i < extra; ++i) {
        edges.push_back(cand[i]);
    }

    // Shuffle full edge list for randomness
    shuffle(edges.begin(), edges.end());

    // Output format: N M K, then M lines of "u v w"
    println(N, M, K);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        int w;
        // Mix small and large weights
        if (rnd.next() < 0.3) 
            w = rnd.next(1, 10);
        else 
            w = rnd.next(1, 1000000);
        println(u, v, w);
    }

    return 0;
}
