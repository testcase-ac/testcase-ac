#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of vertices
    int N = rnd.next(2, 10);
    // Weight range hyper-parameters
    int lowW = rnd.next(0, 50);
    int highW = rnd.next(lowW, 100000);
    // Probability to reuse an existing weight for extra edges
    double equalWeightProb = rnd.next(0.0, 1.0);

    // Build a random spanning tree to ensure connectivity
    vector<pair<int,int>> treeEdges;
    for (int v = 2; v <= N; ++v) {
        int u = rnd.next(1, v - 1);
        treeEdges.emplace_back(u, v);
    }
    // Mark used edges
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    for (auto &e : treeEdges) {
        used[e.first][e.second] = used[e.second][e.first] = true;
    }

    // Assign weights to the tree edges
    vector<tuple<int,int,int>> edges;
    vector<int> treeWeights;
    for (auto &e : treeEdges) {
        int w = rnd.next(lowW, highW);
        treeWeights.push_back(w);
        edges.emplace_back(e.first, e.second, w);
    }

    // Collect candidate extra edges (to create cycles)
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (!used[i][j]) {
                cand.emplace_back(i, j);
            }
        }
    }
    shuffle(cand.begin(), cand.end());

    // Decide how many extra edges, but keep total edges <= 20
    int maxExtraByCap = max(0, 20 - (int)treeEdges.size());
    int extraAvail = cand.size();
    int extra = rnd.next(0, min(extraAvail, maxExtraByCap));
    for (int i = 0; i < extra; ++i) {
        int u = cand[i].first, v = cand[i].second;
        int w;
        if (!treeWeights.empty() && rnd.next() < equalWeightProb) {
            // reuse a tree weight
            w = rnd.any(treeWeights);
        } else {
            w = rnd.next(lowW, highW);
        }
        edges.emplace_back(u, v, w);
    }

    // Final shuffle of all edges
    shuffle(edges.begin(), edges.end());

    // Output
    int M = edges.size();
    println(N, M);
    for (auto &t : edges) {
        int u, v, w;
        tie(u, v, w) = t;
        println(u, v, w);
    }
    return 0;
}
