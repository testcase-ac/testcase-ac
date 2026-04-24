#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of nodes
    int N = rnd.next(2, 10);

    // Hyper-parameter: tree shape (0 = chain, 1 = star, 2 = random)
    int shape = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    for (int i = 2; i <= N; ++i) {
        if (shape == 0) {
            // chain
            edges.emplace_back(i - 1, i);
        } else if (shape == 1) {
            // star centered at 1
            edges.emplace_back(1, i);
        } else {
            // random tree
            int j = rnd.next(1, i - 1);
            edges.emplace_back(j, i);
        }
    }

    // Optionally shuffle edge order for diversity
    if (rnd.next() < 0.5) {
        shuffle(edges.begin(), edges.end());
    }

    // Output tree
    println(N);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    // Hyper-parameter: number of queries
    int Q = rnd.next(1, 20);
    // Probability of type-1 (toggle) vs type-2 (query)
    double pToggle = rnd.next();

    // Generate query types
    vector<int> types(Q);
    for (int i = 0; i < Q; ++i) {
        types[i] = (rnd.next() < pToggle ? 1 : 2);
    }
    // Ensure at least one type-2 query
    bool hasQuery = false;
    for (int t : types) if (t == 2) { hasQuery = true; break; }
    if (!hasQuery) {
        int pos = rnd.next(0, Q - 1);
        types[pos] = 2;
    }

    // Output queries
    println(Q);
    for (int i = 0; i < Q; ++i) {
        int t = types[i];
        int x = rnd.next(1, N);
        println(t, x);
    }

    return 0;
}
