#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices
    int V = rnd.next(2, 10);

    // Number of SCCs (hyper-parameter)
    int K = rnd.next(1, V);

    // Partition V into K groups (each at least size 1)
    vector<int> gsize(K, 1);
    int rem = V - K;
    for (int i = 0; i < rem; i++) {
        gsize[rnd.next(0, K-1)]++;
    }

    // Assign vertices 1..V to groups 0..K-1
    vector<int> groupOf(V);
    int cur = 0;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < gsize[i]; j++) {
            groupOf[cur++] = i;
        }
    }

    // Build list of vertices per group
    vector<vector<int>> groups(K);
    for (int v = 0; v < V; v++) {
        groups[groupOf[v]].push_back(v + 1);
    }

    // Hyper-parameters for edge densities
    double pin = rnd.next();  // internal edge extra density
    double pex = rnd.next();  // inter-group edge density

    vector<pair<int,int>> edges;

    // Create internal edges to guarantee strong connectivity in each group
    for (int i = 0; i < K; i++) {
        auto &G = groups[i];
        int sz = (int)G.size();
        if (sz >= 2) {
            // make a directed cycle
            for (int j = 0; j < sz; j++) {
                int u = G[j], v = G[(j+1)%sz];
                edges.emplace_back(u, v);
            }
            // and reverse cycle to ensure strong connectivity
            for (int j = 0; j < sz; j++) {
                int u = G[(j+1)%sz], v = G[j];
                edges.emplace_back(u, v);
            }
        }
        // add some extra random internal edges
        for (int a = 0; a < sz; a++) {
            for (int b = 0; b < sz; b++) {
                if (a != b && rnd.next() < pin) {
                    edges.emplace_back(G[a], G[b]);
                }
            }
        }
    }

    // Add some edges between groups in a DAG fashion (i -> j for i<j)
    for (int i = 0; i < K; i++) {
        for (int j = i + 1; j < K; j++) {
            for (int u : groups[i]) {
                for (int v : groups[j]) {
                    if (rnd.next() < pex) {
                        edges.emplace_back(u, v);
                    }
                }
            }
        }
    }

    // Ensure at least one edge
    if (edges.empty()) {
        int u = rnd.next(1, V);
        int v = rnd.next(1, V);
        while (v == u) v = rnd.next(1, V);
        edges.emplace_back(u, v);
    }

    // Remove duplicates
    set<pair<int,int>> seen;
    vector<pair<int,int>> uniq;
    for (auto &e : edges) {
        if (seen.insert(e).second) {
            uniq.push_back(e);
        }
    }

    // Shuffle and output
    shuffle(uniq.begin(), uniq.end());
    println(V, (int)uniq.size());
    for (auto &e : uniq) {
        println(e.first, e.second);
    }
    return 0;
}
