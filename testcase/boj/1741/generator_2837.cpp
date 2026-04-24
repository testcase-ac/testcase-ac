#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: bias for n
    vector<int> tns = {-2, -1, 0, 1, 2};
    int t_n = rnd.any(tns);
    // n in [2..10], biased by wnext
    int n = rnd.wnext(9, t_n) + 2;

    // Hyper-parameter: choose k either uniform or biased
    int k;
    if (rnd.next(0, 1) == 0) {
        k = rnd.next(2, n);
    } else {
        vector<int> signs = {-1, 1};
        int t_k = rnd.any(signs);
        // k in [2..n], biased by wnext
        k = rnd.wnext(n - 1, t_k) + 2;
        if (k > n) k = n;
    }

    // Build a random partition of n into k positive parts
    vector<int> sizes(k, 1);
    int rem = n - k;
    for (int i = 0; i < rem; ++i) {
        int idx = rnd.next(k);  // [0..k-1]
        sizes[idx]++;
    }

    // Assign node labels randomly to the parts
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    vector<int> part(n + 1);
    int ptr = 0;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < sizes[i]; ++j) {
            part[nodes[ptr++]] = i;
        }
    }

    // Build the complete k-partite graph: edges only between different parts
    vector<pair<int,int>> edges;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (part[u] != part[v]) {
                edges.emplace_back(u, v);
            }
        }
    }

    // Shuffle edges to vary order
    shuffle(edges.begin(), edges.end());

    // Output in the required format
    println(n, int(edges.size()));
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
