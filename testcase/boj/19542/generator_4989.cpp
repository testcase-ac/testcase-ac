#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size
    int N = rnd.next(1, 10);

    // Choose tree shape: 0=chain, 1=star, 2=random
    int treeType = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (treeType == 0) {
        // Chain 1-2-3-...-N
        for (int i = 2; i <= N; ++i) {
            edges.emplace_back(i-1, i);
        }
    } else if (treeType == 1) {
        // Star centered at c
        int c = rnd.next(1, N);
        for (int i = 1; i <= N; ++i) {
            if (i != c) edges.emplace_back(c, i);
        }
    } else {
        // Random tree by linking i to a random previous node
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    }

    // Shuffle edges for randomness
    shuffle(edges.begin(), edges.end());

    // Compute degrees to find leaves
    vector<int> deg(N+1, 0);
    for (auto &e : edges) {
        deg[e.first]++;
        deg[e.second]++;
    }
    vector<int> leaves;
    for (int i = 1; i <= N; ++i) {
        if (deg[i] <= 1) leaves.push_back(i);
    }
    if (leaves.empty()) leaves.push_back(1); // fallback for N=0? but N>=1

    // Choose starting node S: sometimes a leaf, sometimes any
    int S;
    if (rnd.next() < 0.5) {
        S = rnd.any(leaves);
    } else {
        S = rnd.next(1, N);
    }

    // Choose D with varied distributions
    double p = rnd.next();
    int D;
    if (p < 0.3) {
        D = 0;
    } else if (p < 0.6) {
        D = rnd.wnext(N+1, -1); // bias low
    } else if (p < 0.9) {
        D = rnd.wnext(N+1, +1); // bias high
    } else {
        D = rnd.next(0, N);
    }

    // Output
    println(N, S, D);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
