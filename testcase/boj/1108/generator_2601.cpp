/* generator code */
#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of websites (lines)
    int K = rnd.next(1, 10);

    // Generate unique site names (single uppercase letters)
    vector<string> names;
    for (int i = 0; i < K; i++) {
        names.push_back(string(1, char('A' + i)));
    }
    // Shuffle the names for randomness
    shuffle(names.begin(), names.end());

    // Build all possible directed edges u->v, u!=v
    vector<pair<int,int>> edges;
    for (int u = 0; u < K; u++) {
        for (int v = 0; v < K; v++) {
            if (u == v) continue;
            edges.emplace_back(u, v);
        }
    }

    // Choose a random density between 20% and 70%
    double density = rnd.next(0.2, 0.7);

    // Filter edges by density
    vector<pair<int,int>> chosen;
    for (auto &e : edges) {
        if (rnd.next() < density) {
            chosen.push_back(e);
        }
    }

    // Build parent lists: parent[v] = list of u such that u->v
    vector<vector<int>> parent(K);
    for (auto &e : chosen) {
        parent[e.second].push_back(e.first);
    }

    // Output number of link-info lines
    println(K);
    // Each line: siteName numParents [parentNames...]
    for (int i = 0; i < K; i++) {
        // Shuffle parent order for diversity
        shuffle(parent[i].begin(), parent[i].end());
        printf("%s %d", names[i].c_str(), int(parent[i].size()));
        for (int u : parent[i]) {
            printf(" %s", names[u].c_str());
        }
        printf("\n");
    }

    // Query: pick a random site
    int q = rnd.next(0, K - 1);
    println(names[q]);

    return 0;
}
