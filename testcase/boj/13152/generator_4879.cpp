#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int n = rnd.next(1, 10);

    // Build all possible undirected roads
    vector<pair<int,int>> edges;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            edges.emplace_back(i, j);

    // Shuffle for randomness
    shuffle(edges.begin(), edges.end());

    // Hyper-parameter: density choice
    double density = rnd.next(0.0, 1.0);

    // Select edges with given density, cap at 20 for hand-checkable size
    vector<pair<int,int>> chosen;
    for (auto &e : edges) {
        if (rnd.next() < density) {
            chosen.push_back(e);
            if (chosen.size() >= 20) break;
        }
    }

    // Ensure at least one edge if possible
    if (n > 1 && chosen.empty()) {
        int idx = rnd.next((int)edges.size());
        chosen.push_back(edges[idx]);
    }

    // Output in required format
    println(n);
    println((int)chosen.size());
    for (auto &e : chosen) {
        println(e.first, e.second);
    }

    return 0;
}
