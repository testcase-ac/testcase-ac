#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for small, hand-checkable sizes
    int n = rnd.next(2, 10);          // number of intersections
    int b = rnd.next(1, n - 1);       // number of branch offices at nodes 1..b
    int s = rnd.next(1, b);           // number of subprojects
    int maxPossibleEdges = n * (n - 1);
    int rmax = min(maxPossibleEdges, 20);
    int r = rnd.next(n, rmax);        // number of directed roads

    // Hyper-parameter for edge-length diversity
    vector<int> maxLenChoices = {0, 5, 10, 100, 1000, 10000};
    int maxLen = rnd.any(maxLenChoices);

    // Build a base directed cycle to ensure strong connectivity
    vector<tuple<int,int,int>> edges;
    set<pair<int,int>> used;
    for (int i = 1; i < n; i++) {
        used.insert({i, i+1});
        edges.emplace_back(i, i+1, rnd.next(0, maxLen));
    }
    used.insert({n, 1});
    edges.emplace_back(n, 1, rnd.next(0, maxLen));

    // Build list of all other possible directed edges (no self-loops, no duplicates)
    vector<pair<int,int>> candidates;
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (u == v) continue;
            if (used.count({u, v}) == 0) {
                candidates.emplace_back(u, v);
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    // Add random edges until we reach r edges total
    for (int i = 0; edges.size() < (size_t)r && i < (int)candidates.size(); i++) {
        auto [u, v] = candidates[i];
        used.insert({u, v});
        edges.emplace_back(u, v, rnd.next(0, maxLen));
    }

    // Final shuffle to randomize order of edges
    shuffle(edges.begin(), edges.end());

    // Output
    println(n, b, s, r);
    for (auto &e : edges) {
        int u, v, l;
        tie(u, v, l) = e;
        println(u, v, l);
    }
    return 0;
}
