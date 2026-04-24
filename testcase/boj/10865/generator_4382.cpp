#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of students
    int N = rnd.next(1, 10);
    long long maxEdges = 1LL * N * (N - 1) / 2;

    // Hyper-parameter to bias edge count: t>0 for dense bias, t<0 for sparse bias
    int t = rnd.next(-2, 2);
    int M = (maxEdges > 0 ? rnd.wnext((int)(maxEdges + 1), t) : 0);

    // Build all possible undirected friend pairs
    vector<pair<int,int>> edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.emplace_back(i, j);
        }
    }
    // Randomly pick M edges
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    // Randomly decide to swap direction of some edges for diversity
    double swapProb = rnd.next();
    for (auto &e : edges) {
        if (rnd.next() < swapProb) {
            swap(e.first, e.second);
        }
    }

    // Output
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
