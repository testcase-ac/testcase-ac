#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of nodes between 3 and 15, biased towards smaller
    int N = rnd.wnext(13, -1) + 3;
    // Build all possible directed edges without self-loops
    vector<pair<int,int>> allEdges;
    for (int u = 1; u <= N; ++u)
        for (int v = 1; v <= N; ++v)
            if (u != v)
                allEdges.emplace_back(u, v);
    shuffle(allEdges.begin(), allEdges.end());
    // Hyper-parameter: edge inclusion probability
    vector<double> probs = {0.1, 0.3, 0.5, 0.8};
    double p = rnd.any(probs);
    // Hyper-parameter: maximum weight
    vector<int> weightCaps = {10, 100, 1000, 10000};
    int Wmax = rnd.any(weightCaps);
    // Select edges
    vector<array<int,3>> edges;
    for (auto &e : allEdges) {
        if (rnd.next() < p) {
            edges.push_back({e.first, e.second, rnd.next(1, Wmax)});
        }
    }
    // Ensure at least one edge
    if (edges.empty()) {
        auto &e = allEdges[0];
        edges.push_back({e.first, e.second, rnd.next(1, Wmax)});
    }
    int M = edges.size();
    // Choose distinct X, Y, Z
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    int X = nodes[0], Y = nodes[1], Z = nodes[2];
    // Output
    println(N, M);
    for (auto &ed : edges)
        println(ed[0], ed[1], ed[2]);
    println(X, Y, Z);
    return 0;
}
