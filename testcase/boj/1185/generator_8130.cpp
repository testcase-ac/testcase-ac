#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of countries: between 5 and 15, bias towards small
    int N = rnd.wnext(11, -1) + 5;  // rnd.wnext(11,-1) in [0,10], so N in [5,15]
    int full = N * (N - 1) / 2;
    // Number of roads: between N-1 and full
    int P = rnd.next(N - 1, full);

    // Node costs range hyper-parameters
    int costMin = rnd.next(1, 1000);
    int costMax = rnd.next(costMin, 1000);
    vector<int> C(N + 1);
    for (int i = 1; i <= N; i++) {
        C[i] = rnd.next(costMin, costMax);
    }

    // Edge length range hyper-parameters
    int lenMin = rnd.next(0, 1000);
    int lenMax = rnd.next(lenMin, 1000);

    // Choose a spanning tree structure: 0=random, 1=chain, 2=star
    int treeType = rnd.next(0, 2);
    vector<pair<int,int>> treeEdges;
    if (treeType == 0) {
        // random tree by random parent
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            treeEdges.emplace_back(p, i);
        }
    } else if (treeType == 1) {
        // chain
        for (int i = 1; i < N; i++) {
            treeEdges.emplace_back(i, i + 1);
        }
    } else {
        // star centered at 1
        for (int i = 2; i <= N; i++) {
            treeEdges.emplace_back(1, i);
        }
    }

    // Mark used edges in the tree
    vector<vector<bool>> used(N + 1, vector<bool>(N + 1, false));
    for (auto &e : treeEdges) {
        used[e.first][e.second] = used[e.second][e.first] = true;
    }

    // Build list of extra possible edges
    vector<pair<int,int>> extra;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (!used[i][j]) extra.emplace_back(i, j);
        }
    }
    // Shuffle and take as many as needed
    shuffle(extra.begin(), extra.end());
    int need = P - (N - 1);
    vector<pair<int,int>> edges = treeEdges;
    for (int i = 0; i < need; i++) {
        edges.push_back(extra[i]);
    }
    // Shuffle final edge list
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, P);
    for (int i = 1; i <= N; i++) {
        println(C[i]);
    }
    for (auto &e : edges) {
        int w = rnd.next(lenMin, lenMax);
        println(e.first, e.second, w);
    }

    return 0;
}
