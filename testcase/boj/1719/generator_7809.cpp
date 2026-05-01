#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes: small enough to verify, but variable
    int n = rnd.next(2, 15);

    // Build a random spanning tree to ensure connectivity
    vector<pair<int,int>> tree;
    set<pair<int,int>> used;
    for (int i = 2; i <= n; ++i) {
        int j = rnd.next(1, i - 1);
        tree.emplace_back(j, i);
        used.insert({min(j, i), max(j, i)});
    }

    // Build remaining candidate edges
    vector<pair<int,int>> candidates;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (!used.count({i, j})) {
                candidates.emplace_back(i, j);
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    // Hyper-parameter to control extra edge count (density bias)
    vector<int> densBias = { -2, -1, 0, 1, 2 };
    int tEdge = rnd.any(densBias);
    int maxExtra = candidates.size();
    int remEdges = rnd.wnext(maxExtra + 1, tEdge); // [0, maxExtra]

    vector<pair<int,int>> extras(candidates.begin(), candidates.begin() + remEdges);

    // Hyper-parameters for weights
    int wmin = rnd.next(1, 5);
    int wmax = rnd.next(wmin, 100);
    int tW = rnd.any(densBias);
    auto genWeight = [&]() {
        int range = wmax - wmin + 1;
        return rnd.wnext(range, tW) + wmin;
    };

    // Combine edges and assign weights
    struct Edge { int u, v, w; };
    vector<Edge> edges;
    for (auto &e : tree)
        edges.push_back({e.first, e.second, genWeight()});
    for (auto &e : extras)
        edges.push_back({e.first, e.second, genWeight()});

    // Shuffle output order
    shuffle(edges.begin(), edges.end());

    // Output
    println(n, edges.size());
    for (auto &e : edges)
        println(e.u, e.v, e.w);

    return 0;
}
