#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total people
    int N = rnd.next(1, 30);
    // Number of components (committees)
    int K = rnd.next(1, min(N, 10));
    // Allocate at least 1 per component
    vector<int> comp_size(K, 1);
    // Distribute the remaining N-K people randomly
    for (int i = 0; i < N - K; i++) {
        int idx = rnd.next(0, K - 1);
        comp_size[idx]++;
    }

    vector<pair<int,int>> edges;
    int curr_label = 1;
    // Build each component with a random spanning tree + extra edges
    for (int ci = 0; ci < K; ci++) {
        int sz = comp_size[ci];
        // Collect vertex labels for this component
        vector<int> vs(sz);
        for (int i = 0; i < sz; i++) {
            vs[i] = curr_label++;
        }
        // Shuffle for randomness
        shuffle(vs.begin(), vs.end());
        // Build a random spanning tree
        vector<pair<int,int>> compEdges;
        set<pair<int,int>> used;
        for (int i = 1; i < sz; i++) {
            int a = vs[i];
            int b = vs[rnd.next(0, i - 1)];
            int u = min(a, b), v = max(a, b);
            compEdges.emplace_back(u, v);
            used.insert({u, v});
        }
        // Add extra edges with varied density
        int max_extra = sz * (sz - 1) / 2 - max(0, sz - 1);
        if (max_extra > 0) {
            vector<int> tvals = {-1, 0, 1, 2};
            int t = rnd.any(tvals);
            int extra = rnd.wnext(max_extra + 1, t);
            // Collect all possible missing edges
            vector<pair<int,int>> cand;
            for (int i = 0; i < sz; i++) {
                for (int j = i + 1; j < sz; j++) {
                    int u = min(vs[i], vs[j]);
                    int v = max(vs[i], vs[j]);
                    if (!used.count({u, v})) {
                        cand.emplace_back(u, v);
                    }
                }
            }
            shuffle(cand.begin(), cand.end());
            extra = min(extra, (int)cand.size());
            for (int i = 0; i < extra; i++) {
                compEdges.push_back(cand[i]);
            }
        }
        // Merge into global edge list
        edges.insert(edges.end(), compEdges.begin(), compEdges.end());
    }

    // Shuffle all edges for randomness
    shuffle(edges.begin(), edges.end());
    // Output in correct format
    println(N);
    println((int)edges.size());
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
