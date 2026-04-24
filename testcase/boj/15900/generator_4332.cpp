#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of nodes
    int N = rnd.next(2, 10);

    // Hyper-parameter: type of tree
    int type = rnd.next(0, 2); // 0: path, 1: star, 2: random

    vector<pair<int,int>> edges;
    if (type == 0) {
        // path 1-2-3-...-N
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(i-1, i);
        }
    } else if (type == 1) {
        // star centered at random c in [1..N]
        int c = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i == c) continue;
            edges.emplace_back(c, i);
        }
    } else {
        // random tree by attaching i to random earlier node
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    }

    // Shuffle edge list
    shuffle(edges.begin(), edges.end());

    // Randomly swap endpoints in some edges for diversity (undirected)
    double swapProb = rnd.next();
    for (auto &e : edges) {
        if (rnd.next() < swapProb) {
            swap(e.first, e.second);
        }
    }

    // Keep root as label 1, randomly permute other labels
    vector<int> perm(N+1);
    perm[1] = 1;
    vector<int> rest;
    for (int i = 2; i <= N; i++) rest.push_back(i);
    shuffle(rest.begin(), rest.end());
    for (int i = 2; i <= N; i++) perm[i] = rest[i-2];

    // Apply permutation to edges
    for (auto &e : edges) {
        e.first = perm[e.first];
        e.second = perm[e.second];
    }

    // Output
    println(N);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
