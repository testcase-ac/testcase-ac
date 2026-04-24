#include "testlib.h"
#include <vector>
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Hyperparameters with randomization
    int N = rnd.next(2, 10);  // Small number of users for verification
    double density = rnd.next(0.1, 0.9);  // Controls graph density
    int max_possible_edges = N * (N - 1) / 2;
    int M = rnd.next(1, min(max_possible_edges, (int)(density * max_possible_edges) + 1));
    
    // Ensure the graph is connected by first creating a spanning tree
    set<pair<int, int>> edges;
    vector<int> nodes(N);
    for (int i = 0; i < N; i++) nodes[i] = i + 1;
    shuffle(nodes.begin(), nodes.end());
    
    // Create spanning tree to ensure connectivity
    for (int i = 1; i < N; i++) {
        int parent = rnd.next(0, i - 1);
        int u = nodes[parent];
        int v = nodes[i];
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }
    
    // Add remaining edges randomly
    while (edges.size() < M) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        if (u == v) continue;
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }
    
    // Convert to vector for shuffling
    vector<pair<int, int>> edge_list(edges.begin(), edges.end());
    shuffle(edge_list.begin(), edge_list.end());
    
    // Print output
    println(N, edge_list.size());
    for (auto [u, v] : edge_list) {
        println(u, v);
    }
    
    return 0;
}
