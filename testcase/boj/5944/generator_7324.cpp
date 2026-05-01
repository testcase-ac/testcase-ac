#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of pastures P and cowpaths C
    int P = rnd.next(3, 10);
    int maxEdges = P * (P - 1) / 2;
    int treeEdges = P - 1;
    int extraMax = maxEdges - treeEdges;
    // Bias extra edges count to test sparse and dense graphs
    int bias = rnd.next(-1, 1); // -1: few, 0: uniform, 1: many
    int extraCount = rnd.wnext(extraMax + 1, bias);
    int C = treeEdges + extraCount;

    // Choose distinct PB, PA1, PA2
    vector<int> nodes(P);
    for (int i = 0; i < P; i++) nodes[i] = i + 1;
    shuffle(nodes.begin(), nodes.end());
    int PB  = nodes[0];
    int PA1 = nodes[1];
    int PA2 = nodes[2];

    // Build a random spanning tree
    vector<pair<int,int>> tree;
    vector<vector<bool>> used(P+1, vector<bool>(P+1, false));
    // Use a random permutation to connect
    vector<int> perm = nodes;
    // Ensure perm covers all 1..P
    for (int i = 0; i < P; i++) perm[i] = i + 1;
    shuffle(perm.begin(), perm.end());
    for (int i = 1; i < P; i++) {
        int u = perm[i];
        int v = perm[rnd.next(0, i-1)];
        tree.emplace_back(u, v);
        used[u][v] = used[v][u] = true;
    }

    // Prepare candidate extra edges
    vector<pair<int,int>> cand;
    for (int u = 1; u <= P; u++) {
        for (int v = u+1; v <= P; v++) {
            if (!used[u][v]) cand.emplace_back(u, v);
        }
    }
    shuffle(cand.begin(), cand.end());
    // Take extraCount edges
    vector<pair<int,int>> edges = tree;
    for (int i = 0; i < extraCount && i < (int)cand.size(); i++) {
        edges.push_back(cand[i]);
    }
    // Assign weights
    int weightMax = rnd.any(vector<int>{10,20,50});
    vector<tuple<int,int,int>> outEdges;
    for (auto &e : edges) {
        int w = rnd.next(1, weightMax);
        outEdges.emplace_back(e.first, e.second, w);
    }
    // Shuffle final edges for variability
    shuffle(outEdges.begin(), outEdges.end());

    // Output
    println(C, P, PB, PA1, PA2);
    for (auto &t : outEdges) {
        int u, v, w;
        tie(u, v, w) = t;
        println(u, v, w);
    }

    return 0;
}
