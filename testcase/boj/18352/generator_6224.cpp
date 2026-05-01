#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for N: skewed small or large within [2,15]
    int tN = rnd.any(vector<int>{-2, 2});
    int N = rnd.wnext(14, tN) + 2;

    // Starting city X
    int X = rnd.next(1, N);

    // Distance K: allow up to N+3 to test unreachable
    int K = rnd.next(1, N + 3);

    vector<pair<int,int>> edges;

    // Occasionally produce a chain graph to test path distances
    bool chainCase = (rnd.next(0, 4) == 0);
    if (chainCase) {
        // Chain 1->2->...->N
        for (int i = 1; i < N; i++) {
            edges.emplace_back(i, i+1);
        }
    } else {
        // Random directed graph
        int maxEdges = N * (N - 1);
        int tM = rnd.any(vector<int>{-1, 2});
        int Mraw = rnd.wnext(maxEdges + 1, tM);
        int M = max(1, Mraw);

        // Build all possible directed edges
        vector<pair<int,int>> all;
        all.reserve(maxEdges);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i != j) all.emplace_back(i, j);
            }
        }
        shuffle(all.begin(), all.end());
        edges.insert(edges.end(), all.begin(), all.begin() + M);
    }

    int M = edges.size();
    // Output
    println(N, M, K, X);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
