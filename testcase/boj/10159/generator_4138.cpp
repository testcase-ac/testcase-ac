#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of items
    int N = rnd.next(5, 10);

    // Generate a base ordering
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    double ord_choice = rnd.next();
    if (ord_choice < 0.2) {
        // keep identity
    } else if (ord_choice < 0.4) {
        reverse(perm.begin(), perm.end());
    } else {
        shuffle(perm.begin(), perm.end());
    }

    // Hyper-parameter for density: weighted bias
    vector<int> w = {-3, -2, -1, 0, 1, 2, 3};
    int t = rnd.any(w);
    double p = rnd.wnext(101, t) / 100.0;

    // Force some edge cases
    if (rnd.next() < 0.15) p = 0.0;
    else if (rnd.next() < 0.15) p = 1.0;

    // Build a DAG of comparisons
    vector<pair<int,int>> edges;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (rnd.next() < p) {
                edges.emplace_back(perm[i], perm[j]);
            }
        }
    }

    // Shuffle output order
    shuffle(edges.begin(), edges.end());

    // Output format: N, M, then edges
    println(N);
    println((int)edges.size());
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
