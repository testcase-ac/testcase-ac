#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N in small, medium, or larger for variability
    int N;
    if (rnd.next() < 0.3) {
        N = rnd.next(2, 5);
    } else if (rnd.next() < 0.6) {
        N = rnd.next(6, 10);
    } else {
        N = rnd.next(11, 15);
    }
    // Tree shape hyper-parameter: 0=chain, 1=star, 2=random parent
    int treeType = rnd.next(0, 2);
    // Weight distribution: 0=small(1..10), 1=large(1..10000)
    int weightType = rnd.next(0, 1);

    vector<tuple<int,int,int>> edges;
    edges.reserve(N-1);
    for (int i = 2; i <= N; i++) {
        int u, v = i;
        if (treeType == 0) {
            u = i - 1;
        } else if (treeType == 1) {
            u = 1;
        } else {
            u = rnd.next(1, i - 1);
        }
        int w = (weightType == 0 ? rnd.next(1, 10) : rnd.next(1, 10000));
        edges.emplace_back(u, v, w);
    }

    // Output tree
    println(N);
    for (auto &e : edges) {
        println(get<0>(e), get<1>(e), get<2>(e));
    }

    // Generate queries M with clusters
    int maxPairs = N * (N - 1) / 2;
    double rv = rnd.next();
    int M;
    if (rv < 0.3) {
        M = rnd.next(1, min(3, maxPairs));
    } else if (rv < 0.7) {
        M = rnd.next(min(4, maxPairs), min(10, maxPairs));
    } else {
        M = rnd.next(min(11, maxPairs), min(20, maxPairs));
    }

    // Build all distinct pairs then sample without replacement
    vector<pair<int,int>> pairs;
    pairs.reserve(maxPairs);
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            pairs.emplace_back(i, j);
        }
    }
    shuffle(pairs.begin(), pairs.end());
    pairs.resize(M);

    // Output queries, randomly swap order for variability
    println(M);
    for (auto &p : pairs) {
        int u = p.first, v = p.second;
        if (rnd.next() < 0.5) swap(u, v);
        println(u, v);
    }

    return 0;
}
