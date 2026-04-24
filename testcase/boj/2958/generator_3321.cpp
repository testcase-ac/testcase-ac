#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: number of cities
    int N = rnd.next(2, 10);
    int maxEdges = N * (N - 1);
    int M = rnd.next(1, min(maxEdges, 20));

    // Decide whether to allow duplicate roads
    bool allowDup = rnd.next(0, 1);

    // Build all possible directed edges
    vector<pair<int,int>> allEdges;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            if (i != j)
                allEdges.emplace_back(i, j);
    shuffle(allEdges.begin(), allEdges.end());

    // Choose unique edges count
    int uniqueCount = allowDup ? rnd.next(1, M) : M;
    vector<pair<int,int>> chosen;
    for (int i = 0; i < uniqueCount; ++i)
        chosen.push_back(allEdges[i]);

    // If duplicates are allowed, add some duplicates
    vector<pair<int,int>> edges = chosen;
    while ((int)edges.size() < M) {
        edges.push_back(rnd.any(chosen));
    }
    shuffle(edges.begin(), edges.end());

    // Hyperparameter: weight distribution
    int weightCase = rnd.next(0, 2);

    // Output
    println(N, M);
    for (auto &e : edges) {
        int L;
        if (weightCase == 0) {
            // small weights
            L = rnd.next(1, 5);
        } else if (weightCase == 1) {
            // moderate weights
            L = rnd.next(10, 20);
        } else {
            // biased toward higher weights
            L = 1 + rnd.wnext(20, 1);
        }
        println(e.first, e.second, L);
    }

    return 0;
}
