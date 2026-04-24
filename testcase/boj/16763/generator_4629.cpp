#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N
    int N = rnd.next(2, 10);
    int maxEdges = N * (N - 1) / 2;
    // Hyper-parameter for extra edges distribution
    int extraHi = maxEdges - (N - 1) + 1; // so that extra in [0, maxEdges-(N-1)]
    int weightParam = rnd.next(-1, 1);
    int extra = rnd.wnext(extraHi, weightParam);
    int M = (N - 1) + extra;

    // Build a random spanning tree to ensure connectivity to barn N
    vector<int> nodes(N);
    for (int i = 0; i < N; i++) nodes[i] = i + 1;
    shuffle(nodes.begin(), nodes.end());
    vector<pair<int,int>> treeEdges;
    treeEdges.reserve(N-1);
    // To track used edges
    set<pair<int,int>> used;
    for (int i = 1; i < N; i++) {
        int to = nodes[i];
        int from = rnd.next(0, i-1);
        int u = nodes[from], v = to;
        if (u > v) swap(u,v);
        treeEdges.emplace_back(u, v);
        used.insert({u,v});
    }

    // Gather all possible remaining edges
    vector<pair<int,int>> candidates;
    for (int i = 1; i <= N; i++) {
        for (int j = i+1; j <= N; j++) {
            if (!used.count({i,j})) {
                candidates.emplace_back(i,j);
            }
        }
    }
    // Shuffle and pick extra edges
    shuffle(candidates.begin(), candidates.end());
    vector<pair<int,int>> extraEdges;
    extraEdges.insert(extraEdges.end(),
                      candidates.begin(),
                      candidates.begin() + extra);

    // Combine edges
    vector<pair<int,int>> edges = treeEdges;
    edges.insert(edges.end(), extraEdges.begin(), extraEdges.end());
    shuffle(edges.begin(), edges.end());

    // Hyper-parameter for edge weight distribution
    int weightMode = rnd.next(1, 3);

    // Haybales
    int K = rnd.next(1, N);
    vector<pair<int,int>> haybales;
    haybales.reserve(K);
    for (int i = 0; i < K; i++) {
        int pasture = rnd.next(1, N);
        // yum distribution skewed
        int yum = rnd.wnext(20, rnd.next(-1,1)) + 1;
        haybales.emplace_back(pasture, yum);
    }

    // Output
    println(N, M, K);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        int t;
        if (weightMode == 1) {
            // uniform small
            t = rnd.next(1, 10);
        } else if (weightMode == 2) {
            // skewed small
            t = rnd.wnext(10, rnd.next(1,3)) + 1;
        } else {
            // skewed larger
            t = rnd.wnext(1000, rnd.next(-2,2)) + 1;
        }
        println(u, v, t);
    }
    for (auto &h : haybales) {
        println(h.first, h.second);
    }

    return 0;
}
