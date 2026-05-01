/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int n = rnd.next(2, 10);

    // Build all possible directed edges i->j, i != j
    vector<pair<int,int>> all;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) all.emplace_back(i, j);
        }
    }

    // Shuffle and pick a small number of edges
    shuffle(all.begin(), all.end());
    int maxEdges = min((int)all.size(), 20);
    int m = rnd.next(1, maxEdges);

    // Choose a cost cap for diversity
    vector<int> caps = {10, 50, 100};
    int cap = rnd.any(caps);

    // Output
    println(n);
    println(m);
    for (int i = 0; i < m; i++) {
        int u = all[i].first;
        int v = all[i].second;
        int c = rnd.next(1, cap);
        println(u, v, c);
    }

    return 0;
}
