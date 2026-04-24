#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of groups of 3: between 1 and 4 (so N = 3..12)
    int g = rnd.next(1, 4);
    int N = g * 3;

    // Decide solvable or not; N=3 always solvable
    bool solvable = (N == 3) || rnd.next(0, 1) == 1;
    vector<pair<int,int>> edges;

    if (solvable) {
        // Partition nodes into connected triples, then link groups into a tree
        vector<int> ids(N);
        iota(ids.begin(), ids.end(), 1);
        shuffle(ids.begin(), ids.end());

        vector<vector<int>> groups(g, vector<int>(3));
        for (int i = 0; i < g; i++) {
            for (int j = 0; j < 3; j++) {
                groups[i][j] = ids[i * 3 + j];
            }
            // make each group a small path
            edges.emplace_back(groups[i][0], groups[i][1]);
            edges.emplace_back(groups[i][1], groups[i][2]);
        }
        // connect the groups in a chain to keep the whole graph a tree
        for (int i = 0; i + 1 < g; i++) {
            int u = rnd.any(groups[i]);
            int v = rnd.any(groups[i + 1]);
            edges.emplace_back(u, v);
        }
    } else {
        // Generate a star with center c and N-1 leaves -> unsolvable for N>=6
        int c = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i == c) continue;
            edges.emplace_back(c, i);
        }
    }

    // Shuffle edges to avoid any ordering bias
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
