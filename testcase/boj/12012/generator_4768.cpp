#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for N and M distribution
    vector<int> weightOptions = {-1, 0, 1};
    int weightN = rnd.any(weightOptions);
    // N in [2,10], biased by weightN
    int N = rnd.wnext(9, weightN) + 2;
    int maxEdges = N * (N - 1) / 2;
    int weightM = rnd.any(weightOptions);
    // M in [1, maxEdges], biased by weightM
    int M = rnd.wnext(maxEdges, weightM) + 1;

    // Build all possible edges
    vector<pair<int,int>> edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.emplace_back(i, j);
        }
    }
    // Shuffle and take first M edges
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    // Output N, M and the edges
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    // Generate a random closing order permutation of barns 1..N
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());
    for (int x : perm) {
        println(x);
    }

    return 0;
}
