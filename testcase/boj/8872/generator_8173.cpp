#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes
    int N = rnd.next(5, 12);

    // Number of existing edges M, avoid triggering the simple-path subtask (M == N-2)
    int M;
    do {
        M = rnd.next(0, N - 1);
    } while (M == N - 2);

    // Cost of newly added edges
    int L = rnd.next(1, 20);

    // Compute number of components
    int C = N - M;

    // Shuffle node labels
    vector<int> nodes(N);
    iota(nodes.begin(), nodes.end(), 0);
    shuffle(nodes.begin(), nodes.end());

    // Randomly partition N nodes into C components (each at least size 1)
    vector<int> compSize(C, 1);
    int rem = N - C;
    for (int i = 0; i < rem; i++) {
        compSize[rnd.next(0, C - 1)]++;
    }

    // Build a forest: for each component, generate a random tree if size > 1
    vector<tuple<int,int,int>> edges;
    int ptr = 0;
    for (int ci = 0; ci < C; ci++) {
        int sz = compSize[ci];
        vector<int> comp(nodes.begin() + ptr, nodes.begin() + ptr + sz);
        ptr += sz;
        if (sz > 1) {
            shuffle(comp.begin(), comp.end());
            for (int i = 1; i < sz; i++) {
                int u = comp[i];
                int v = comp[rnd.next(0, i - 1)];
                int w = rnd.next(1, 10);
                edges.emplace_back(u, v, w);
            }
        }
    }

    // Shuffle edges for randomness
    shuffle(edges.begin(), edges.end());

    // Output the test case
    println(N, M, L);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }

    return 0;
}
