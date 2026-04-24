#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Number of dominos
        int N = rnd.next(1, 10);

        // Decide number of SCC components
        int k = rnd.next(1, N);

        // Partition N nodes into k non-empty components
        vector<int> sizes(k, 1);
        for (int i = 0; i < N - k; i++) {
            sizes[rnd.next(0, k - 1)]++;
        }

        // Assign component ids to nodes
        vector<int> comp(N);
        int idx = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < sizes[i]; j++) {
                comp[idx++] = i;
            }
        }
        shuffle(comp.begin(), comp.end());

        // Group nodes by component
        vector<vector<int>> nodes_in_comp(k);
        for (int i = 0; i < N; i++) {
            nodes_in_comp[comp[i]].push_back(i + 1);
        }

        // Hyperparameters for density
        double p_intern = rnd.next(0.0, 1.0);
        double p_cross = rnd.next(0.0, 1.0);

        set<pair<int,int>> edgeset;

        // Make each component strongly connected (a simple cycle)
        for (int c = 0; c < k; c++) {
            auto &vec = nodes_in_comp[c];
            if ((int)vec.size() > 1) {
                shuffle(vec.begin(), vec.end());
                for (int i = 0; i < (int)vec.size(); i++) {
                    int u = vec[i];
                    int v = vec[(i + 1) % vec.size()];
                    edgeset.insert({u, v});
                }
            }
            // Add extra internal edges
            for (int u : vec) {
                for (int v : vec) {
                    if (u != v && rnd.next() < p_intern) {
                        edgeset.insert({u, v});
                    }
                }
            }
        }

        // Build a random DAG between components
        vector<int> comp_order(k);
        for (int i = 0; i < k; i++) comp_order[i] = i;
        shuffle(comp_order.begin(), comp_order.end());
        for (int i = 0; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                if (rnd.next() < p_cross) {
                    // edge from comp_order[i] -> comp_order[j]
                    auto &A = nodes_in_comp[comp_order[i]];
                    auto &B = nodes_in_comp[comp_order[j]];
                    // pick random reps
                    int u = rnd.any(A);
                    int v = rnd.any(B);
                    edgeset.insert({u, v});
                }
            }
        }

        // Collect and shuffle edges
        vector<pair<int,int>> edges(edgeset.begin(), edgeset.end());
        shuffle(edges.begin(), edges.end());

        // Output
        println(N, (int)edges.size());
        for (auto &e : edges) {
            println(e.first, e.second);
        }
    }
    return 0;
}
