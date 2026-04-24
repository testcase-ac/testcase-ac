#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: number of vertices skewed to larger
    int n = rnd.wnext(9, 1) + 2; // n in [2,10], skew towards higher

    // Prepare shuffled labels for randomness in tree shape
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());

    // Choose tree shape: 0=chain, 1=star, 2=random tree
    int treeType = rnd.next(0, 2);

    vector<pair<int,int>> edges;
    if (treeType == 0) {
        // Chain along permuted order
        for (int i = 1; i < n; i++) {
            int u = perm[i-1], v = perm[i];
            edges.emplace_back(min(u,v), max(u,v));
        }
    } else if (treeType == 1) {
        // Star with random center
        int center = rnd.any(perm);
        for (int v : perm) {
            if (v != center) {
                edges.emplace_back(min(v,center), max(v,center));
            }
        }
    } else {
        // Random spanning tree via parent selection
        for (int i = 1; i < n; i++) {
            int u = perm[i];
            int pi = rnd.next(0, i-1);
            int v = perm[pi];
            edges.emplace_back(min(u,v), max(u,v));
        }
    }

    // Compute how many extra edges we can add
    int maxExtraPossible = n*(n-1)/2 - (n-1);
    int extraLimit = min(maxExtraPossible, 5);
    // Skew extra edges towards small via minimum of two samples
    int extraCount = rnd.wnext(extraLimit + 1, -1);

    // Build list of possible extra edges
    vector<pair<int,int>> candidates;
    vector<vector<bool>> used(n+1, vector<bool>(n+1, false));
    for (auto &e : edges)
        used[e.first][e.second] = used[e.second][e.first] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!used[i][j]) candidates.emplace_back(i, j);
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (int i = 0; i < extraCount && i < (int)candidates.size(); i++) {
        edges.push_back(candidates[i]);
    }

    // Shuffle final edge list
    shuffle(edges.begin(), edges.end());

    // Output
    int m = edges.size();
    println(n, m);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
