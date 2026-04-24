#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose odd N between 3 and 11
    int N = rnd.next(1,5) * 2 + 1;
    int maxE = N * (N - 1) / 2;

    // Hyper-parameter: decide sparse or dense comparisons
    bool sparse = rnd.next(0, 1) == 0;
    int M;
    if (sparse) {
        // few comparisons
        M = rnd.next(1, N);
    } else {
        // many comparisons
        M = rnd.next(N, maxE);
    }

    // Generate a random total order of the marbles
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());

    // All possible consistent comparisons (heavier -> lighter)
    vector<pair<int,int>> edges;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            edges.emplace_back(perm[j], perm[i]);
        }
    }
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    // Output
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
