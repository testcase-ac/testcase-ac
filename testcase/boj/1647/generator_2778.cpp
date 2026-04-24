#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// A simple Fisher–Yates shuffle using testlib's rnd
template <typename T>
void myShuffle(vector<T> &a) {
    for (int i = (int)a.size() - 1; i > 0; --i) {
        int j = rnd.next(0, i);
        swap(a[i], a[j]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of houses: small for hand-checking
    int N = rnd.next(2, 10);
    // Maximum possible undirected edges
    int maxEdges = N * (N - 1) / 2;
    // Number of edges: at least a tree, up to complete
    int M = rnd.next(N - 1, maxEdges);

    // Hyper-parameters for edge weights
    int wmax = rnd.next(1, 20);    // max weight before +1
    int bias = rnd.next(-3, 3);    // bias for rnd.wnext

    // 1) Build a random spanning tree to ensure connectivity
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    myShuffle(nodes);
    vector<pair<int,int>> treeEdges;
    for (int i = 1; i < N; ++i) {
        int u = nodes[i];
        int v = nodes[rnd.next(0, i - 1)];
        treeEdges.emplace_back(u, v);
    }

    // 2) Enumerate all possible edges
    vector<pair<int,int>> allEdges;
    allEdges.reserve(maxEdges);
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            allEdges.emplace_back(i, j);
        }
    }

    // 3) Mark tree edges for easy removal
    vector<vector<bool>> isTree(N + 1, vector<bool>(N + 1, false));
    for (auto &e : treeEdges) {
        isTree[e.first][e.second] = isTree[e.second][e.first] = true;
    }

    // 4) Collect non-tree edges as extras
    vector<pair<int,int>> extraEdges;
    extraEdges.reserve(allEdges.size());
    for (auto &e : allEdges) {
        if (!isTree[e.first][e.second])
            extraEdges.push_back(e);
    }

    // 5) Pick exactly M-(N-1) extras
    myShuffle(extraEdges);
    extraEdges.resize(M - (N - 1));

    // 6) Combine tree edges and extras, then shuffle final list
    vector<pair<int,int>> edges = treeEdges;
    edges.insert(edges.end(), extraEdges.begin(), extraEdges.end());
    myShuffle(edges);

    // 7) Output in the required format
    println(N, M);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        int w;
        if (bias != 0) {
            // rnd.wnext can be used for bias>0 (max of samples)
            // or bias<0 (min of samples)
            w = rnd.wnext(wmax, bias) + 1;
        } else {
            w = rnd.next(1, wmax);
        }
        println(u, v, w);
    }

    return 0;
}
