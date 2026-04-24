#include "testlib.h"
#include <numeric>
#include <set>
#include <vector>
using namespace std;
struct Edge { int u, v, c; };
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of vertices
    int V = rnd.next(2, 10);
    int maxE = V * (V - 1);
    // Hyper-parameter to bias edge count toward sparse or dense
    int tParam = rnd.next(-2, 2);
    int Ebase = rnd.wnext(maxE, tParam);
    // Build all possible directed edges
    vector<pair<int,int>> allEdges;
    for (int u = 1; u <= V; ++u)
        for (int v = 1; v <= V; ++v)
            if (u != v)
                allEdges.emplace_back(u, v);
    shuffle(allEdges.begin(), allEdges.end());
    // Choose a random maximum weight
    vector<int> wOpts = {10, 100, 1000, 10000};
    int wMax = rnd.any(wOpts);
    // Pick the first Ebase edges
    set<pair<int,int>> used;
    vector<Edge> edges;
    for (int i = 0; i < Ebase && i < (int)allEdges.size(); ++i) {
        auto pr = allEdges[i];
        used.insert(pr);
        edges.push_back({pr.first, pr.second, rnd.next(1, wMax)});
    }
    // Optionally force at least one small cycle
    if (rnd.next() < 0.5) {
        int L = rnd.next(2, min(V, 4));
        vector<int> nodes(V);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        int wCycleMax = max(1, wMax / 5);
        for (int i = 0; i < L; ++i) {
            int u = nodes[i];
            int v = nodes[(i + 1) % L];
            if (used.insert({u, v}).second) {
                edges.push_back({u, v, rnd.next(1, wCycleMax)});
            }
        }
    }
    // Output
    println(V, (int)edges.size());
    for (auto &e : edges)
        println(e.u, e.v, e.c);
    return 0;
}
