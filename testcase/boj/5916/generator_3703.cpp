#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of farms
    int N = rnd.next(2, 10);

    // Generate a random tree by attaching each new node to a random previous node
    vector<pair<int,int>> edges;
    for (int i = 2; i <= N; ++i) {
        int p = rnd.next(1, i - 1);
        edges.emplace_back(p, i);
    }
    // Shuffle edge order for diversity
    shuffle(edges.begin(), edges.end());

    // Number of queries
    int M = rnd.next(1, 20);
    // Probability of a "P" query
    double probP = rnd.next(0.0, 1.0);

    // Output N, M
    println(N, M);
    // Output tree edges
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    // Generate queries
    for (int i = 0; i < M; ++i) {
        char type = (rnd.next() < probP ? 'P' : 'Q');
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        printf("%c %d %d\n", type, u, v);
    }

    return 0;
}
