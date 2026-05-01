#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with some variability: small or moderate size
    double mode = rnd.next();
    int N;
    if (mode < 0.3) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 50);
    }
    int M = N - 6;  // number of normal vertices

    // Distribute M normals into the 9 core–core paths
    vector<int> p(9, 0);
    for (int i = 0; i < M; i++) {
        p[rnd.next(0, 8)]++;
    }

    // The 9 designated core pairs (1-based indices for cores A,B,C,D,E,F = 1..6)
    vector<pair<int,int>> corePairs = {
        {1,2}, {1,3}, {1,4}, {2,3}, {2,5},
        {3,4}, {3,5}, {4,5}, {5,6}
    };

    // Build edges by inserting chains of normal vertices
    vector<pair<int,int>> edges;
    int cur = 7;  // next normal vertex ID
    for (int k = 0; k < 9; k++) {
        int u = corePairs[k].first;
        int v = corePairs[k].second;
        if (p[k] == 0) {
            edges.emplace_back(u, v);
        } else {
            int last = u;
            for (int t = 0; t < p[k]; t++) {
                int node = cur++;
                edges.emplace_back(last, node);
                last = node;
            }
            edges.emplace_back(last, v);
        }
    }
    // Sanity check
    assert(cur - 1 == N);
    assert((int)edges.size() == N + 3);

    // Randomize edge order
    shuffle(edges.begin(), edges.end());

    // Create a random labeling 1..N ensuring label(D) > label(B):
    // core B = original node 2, core D = original node 4
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    do {
        shuffle(perm.begin(), perm.end());
    } while (perm[3] <= perm[1]);

    // Output
    println(N);
    for (auto &e : edges) {
        // relabel endpoints
        int x = perm[e.first - 1];
        int y = perm[e.second - 1];
        printf("%d %d\n", x, y);
    }

    return 0;
}
