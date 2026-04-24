#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of nodes
    int N = rnd.next(2, 10);

    // Prepare labels
    vector<int> labels(N);
    iota(labels.begin(), labels.end(), 1);

    // Pick distinct A, B
    shuffle(labels.begin(), labels.end());
    int A = labels[0];
    int B = labels[1];

    // Hyper-parameter: number of intermediate nodes k
    int maxK = min(3, N - 2);
    int K = rnd.next(0, maxK);

    // Choose K intermediate nodes from the remaining labels
    vector<int> C_list;
    for (int i = 0; i < K; i++) {
        C_list.push_back(labels[2 + i]);
    }
    shuffle(C_list.begin(), C_list.end());

    // Build backbone path: A -> C_list... -> B
    vector<int> backbone_nodes;
    backbone_nodes.push_back(A);
    for (int x : C_list) backbone_nodes.push_back(x);
    backbone_nodes.push_back(B);

    // Build a topological order: backbone in order, then the rest
    vector<bool> in_backbone(N+1, false);
    for (int x : backbone_nodes) in_backbone[x] = true;
    vector<int> rest_nodes;
    for (int x = 1; x <= N; x++) {
        if (!in_backbone[x]) rest_nodes.push_back(x);
    }
    shuffle(rest_nodes.begin(), rest_nodes.end());

    vector<int> topo = backbone_nodes;
    topo.insert(topo.end(), rest_nodes.begin(), rest_nodes.end());
    vector<int> pos(N+1);
    for (int i = 0; i < N; i++) pos[topo[i]] = i;

    // Prepare used matrix to avoid duplicate edges
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));

    // Backbone edges
    vector<pair<int,int>> edges;
    for (int i = 0; i + 1 < (int)backbone_nodes.size(); i++) {
        int u = backbone_nodes[i];
        int v = backbone_nodes[i+1];
        edges.emplace_back(u, v);
        used[u][v] = true;
    }

    // Candidate extra edges (respecting the topological order)
    vector<pair<int,int>> cand;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            int u = topo[i], v = topo[j];
            if (!used[u][v]) {
                cand.emplace_back(u, v);
            }
        }
    }
    shuffle(cand.begin(), cand.end());

    // Hyper-parameter: how many extra edges to add (keep it small)
    int maxExtra = min((int)cand.size(), N);
    int extra = rnd.next(0, maxExtra);

    for (int i = 0; i < extra; i++) {
        auto e = cand[i];
        edges.push_back(e);
    }

    // Shuffle all edges for output
    shuffle(edges.begin(), edges.end());

    int M = edges.size();

    // Output
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    println(A, B, K);
    for (int x : C_list) {
        println(x);
    }

    return 0;
}
