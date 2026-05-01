#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N within problem constraints
    int N = rnd.next(5, 10);
    int maxEdges = N * (N - 1) / 2;

    // Generate M with variety: sparse if t<0, dense if t>0, uniform if t==0
    int t = rnd.next(-2, 2);
    int M;
    if (t == 0) {
        M = rnd.next(1, maxEdges);
    } else {
        M = rnd.wnext(maxEdges, t) + 1;  // rnd.wnext gives [0, maxEdges-1]
    }

    // Starting vertex R
    int R = rnd.next(1, N);

    // Build all possible undirected edges (u < v)
    vector<pair<int,int>> edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.emplace_back(i, j);
        }
    }

    // Shuffle and pick first M edges
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    // Output according to problem specification
    println(N, M, R);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
